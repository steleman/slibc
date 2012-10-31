CXXFLAGS= -fPIC -Wall -pthread -O0 -g $(INCLUDE_DIRS)
CFLAGS= -fPIC -Wall -pthread -O0 -g $(INCLUDE_DIRS)
INCLUDE_DIRS=-I./include -I../include

#CXXFLAGS+=-O0 -fprofile-arcs -ftest-coverage
#CXXFLAGS+=-O0 --coverage

# change to reflect path to the CppUnit-Framework
CPPUNIT_PATH=/usr/include/cppunit

SLIBC_LIB=libslibc.a
SLIBC_LIB_CPP=libslibc++.a

SLIBC_LIB_SH=libslibc.so
SLIBC_LIB_CPP_SH=libslibc++.so

libdir.x86_64 = /usr/lib64
libdir.i686   = /usr/lib

MACHINE := $(shell uname -m)

libdir = $(libdir.$(MACHINE))