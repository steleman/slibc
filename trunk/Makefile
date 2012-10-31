include Makefile.inc

.PHONY: all doc clean_doc clean test slibc tests_slibc tests_ow

all: slibc

archive:
	rm -rf ./gen/
	mkdir ./gen/
	svn export ./ ./gen/slibc-1
	cd ./gen/ && tar czf slibc-1.tar.gz slibc-1/
	rm -rf ./gen/slibc-1

install_devel: test
	mkdir -p $(DESTDIR)$(libdir)/
	cp src/$(SLIBC_LIB) $(DESTDIR)$(libdir)/$(SLIBC_LIB)
	cp src/$(SLIBC_LIB_CPP) $(DESTDIR)$(libdir)/$(SLIBC_LIB_CPP)
	mkdir -p $(DESTDIR)/usr/include/slibc/
	cp -r include/slibc/* $(DESTDIR)/usr/include/slibc/

install: test
	mkdir -p $(DESTDIR)$(libdir)/
	cp src/$(SLIBC_LIB_SH) $(DESTDIR)$(libdir)/$(SLIBC_LIB_SH)
	cp src/$(SLIBC_LIB_CPP_SH) $(DESTDIR)$(libdir)/$(SLIBC_LIB_CPP_SH)	

# build targets
tests_slibc: slibc
	$(MAKE) -C tests_slibc/

tests_ow: slibc
	$(MAKE) -C tests_ow/

slibc:
	$(MAKE) -C src/

test: slibc
	-$(MAKE) -C tests_slibc/ test
	-$(MAKE) -C tests_ow/ test

doc: clean_doc
	doxygen ./slibc.doxy

clean_doc:
	rm -rf doc/html doc/latex doc/man

clean: clean_doc
	$(MAKE) -C src/ clean
	$(MAKE) -C tests_slibc/ clean
	$(MAKE) -C tests_ow/ clean
