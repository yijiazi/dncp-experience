PATHNAME=$(shell pwd)
ifeq ($(findstring Current, $(PATHNAME)),Current)
        XML2RFC="../../00-TOOLS/xml2rfc.tcl"
        RFCDIFF="../../00-TOOLS/rfcdiff"
        COMBINE="../../00-TOOLS/mergexml.sh"
        IDNITS="../../00-TOOLS/idnits"
else
        XML2RFC="../../../00-TOOLS/xml2rfc.tcl"
        RFCDIFF="../../../00-TOOLS/rfcdiff"
        COMBINE="../../../00-TOOLS/mergexml.sh"
        IDNITS="../../../00-TOOLS/idnits"
endif
OBJS=$(shell ls *.xml |grep -v "combined.xml")
#CONVERT="/System/Library/Printers/Libraries/convert"
#CONVERT="/usr/local/bin/convert"
CONVERT="/usr/sbin/cupsfilter"

#TCL_LIBRARY=""

all: $(draftmoniker).pdf $(draftmoniker).html $(draftmoniker).txt $(draftmoniker)-combined.xml rfcdiff.html

%.pdf: %.txt
#	$(CONVERT) -f $< -o $@ 2>/dev/null
	$(CONVERT) $< > $@ 2>/dev/null

$(draftmoniker).txt : $(OBJS)
	$(XML2RFC) $(draftmoniker).xml

$(draftmoniker)-combined.xml : $(OBJS)
	$(COMBINE) $(draftmoniker).xml $(draftmoniker)-combined.xml

$(draftmoniker).html : $(OBJS)
	$(XML2RFC) $(draftmoniker).xml $(draftmoniker).html

rfcdiff.html: PREVIOUS-VERSION.txt $(draftmoniker).txt
	$(RFCDIFF) --stdout PREVIOUS-VERSION.txt $(draftmoniker).txt > rfcdiff.html

presubmission: $(draftmoniker).txt
	$(IDNITS) --verbose $(draftmoniker).txt

clean:
	rm -f $(draftmoniker).txt $(draftmoniker).pdf $(draftmoniker).html rfcdiff.html
