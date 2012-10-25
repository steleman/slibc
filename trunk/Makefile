include Makefile.inc

.PHONY: all doc clean_doc clean test

all: libsc.a

archive:
	rm -rf ./gen/
	mkdir ./gen/
	svn export ./ ./gen/slibc-1
	cd ./gen/ && tar czf slibc-1.tar.gz slibc-1/
	rm -rf ./gen/slibc-1

install: libsc.a test ow
	cp src/$(SLIBC_LIB) $(DESTDIR)$(libdir)/$(SLIBC_LIB)

test_slibc: libsc.a
	$(MAKE) -C tests_slibc/

ow: libsc.a
	$(MAKE) -C tests_ow/

libsc.a:
	$(MAKE) -C src/

test: libsc.a
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


depend: dep

dep:
	makedepend -- $(CXXFLAGS) -- $(SLIBC_OBJS) $(TEST_OBJS)
