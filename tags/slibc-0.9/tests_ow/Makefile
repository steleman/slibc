include ../Makefile.inc

CFLAGS +=-I../include/slibc -Wno-format -Wno-format-extra-args -D__UNIX__ 
LDLIBS +=-L../src/ -lslibc

.PHONY: all clean

OW_TEST_EXES:=safefmt safestr safefile safetime safeio
# we do not compile the wide-char versions as we
# do not support them at the moment
OW_TEST_EXES_W:=  safembyt safewfmt.c safwtime.c

all: $(OW_TEST_EXES)

safefmt:  ../src/$(SLIBC_LIB)
safestr:  ../src/$(SLIBC_LIB)
safefile: ../src/$(SLIBC_LIB)
safetime: ../src/$(SLIBC_LIB)
safeio:   ../src/$(SLIBC_LIB)

test: $(OW_TEST_EXES)
	@echo "\n*********************FILE tests**************************\n"
	-./safefile
	@echo "\n*********************FMT TESTS**************************\n"
	-./safefmt
	@echo "\n*********************IO TESTS**************************\n"
	-./safeio
	@echo "\n*********************STR TESTS**************************\N"
	-./safestr
	@echo "\n*********************Time TESTS**************************\n"
	-./safetime

clean: 
	rm -f $(OW_TEST_EXES) *.o
