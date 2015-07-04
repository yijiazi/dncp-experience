draftmoniker = draft-jin-homenet-dncp-experience


#XML2RFC=$(shell which xml2rfc.tcl)
PATHNAME=$(shell pwd)
ifeq ($(findstring Current, $(PATHNAME)),Current)
        XML2RFC="../Tools/xml2rfc.tcl"
        RFCDIFF="../Tools/rfcdiff"
        COMBINE="../Tools/mergexml.sh"
else
        XML2RFC="../../Tools/xml2rfc.tcl"
        RFCDIFF="../../Tools/rfcdiff"
        COMBINE="../../Tools/mergexml.sh"
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

clean:
	rm -f $(draftmoniker).txt $(draftmoniker).pdf $(draftmoniker).html rfcdiff.html
