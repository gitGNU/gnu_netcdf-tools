### Makefile.am  -*- Makefile-Automake -*-

dist_man_MANS = ncget.1 ncattget.1 ncattput.1

XSLTPROC = xsltproc

## As per foo.1.example_manpage.xml.gz...
%.1 : %.xml
	$(XSLTPROC) \
	    --nonet \
	    --param man.charmap.use.subset 0 \
	    --param make.year.ranges 1 \
	    --param make.single.year.ranges 1 \
	    $<

### Makefile.am ends here
