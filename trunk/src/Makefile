include ../VERSION
include ../Makefile.inc

CFLAGS += -fPIC
CXXFLAGS += -fPIC

.PHONY: all clean

all: $(SLIBC_LIB_SO) $(SLIBC_LIB_CPP_SO)

SLIBC_OBJS=slibc.o stdio_fmt_s.o string_s.o stdio_s.o stdlib_s.o \
	time_s.o stdio_ext_s.o \
	gnu_qsort_s.o gnu_bsearch_s.o gnu_strtok_s.o gnu_vfscanf_s.o 

SLIBC_OBJS_CPP=slibc_cpp.o stdio_fmt_s_cpp.o string_s_cpp.o stdio_s_cpp.o stdlib_s_cpp.o \
	time_s_cpp.o stdio_ext_s_cpp.o \
	gnu_qsort_s_cpp.o gnu_bsearch_s_cpp.o gnu_strtok_s_cpp.o gnu_vfscanf_s_cpp.o 

# static libraries
# $(SLIBC_LIB): $(SLIBC_OBJS)
# 	ar rcs $(SLIBC_LIB) $(SLIBC_OBJS)

# $(SLIBC_LIB_CPP): $(SLIBC_OBJS_CPP)
# 	ar rcs $(SLIBC_LIB_CPP) $(SLIBC_OBJS_CPP)

$(SLIBC_LIB_SO): $(SLIBC_OBJS)
	$(CC) -shared -shared -Wl,-soname,$(SLIBC_LIB_SONAME) -o $(SLIBC_LIB_SO) $(SLIBC_OBJS)
	ln -s -f $(SLIBC_LIB_SO) $(SLIBC_LIB_SONAME)
	ln -s -f $(SLIBC_LIB_SONAME) lib$(SLIBC_NAME).so

$(SLIBC_LIB_CPP_SO): $(SLIBC_OBJS_CPP)
	$(CXX) -shared -shared -Wl,-soname,$(SLIBC_LIB_CPP_SONAME) -o $(SLIBC_LIB_CPP_SO) $(SLIBC_OBJS_CPP)
	ln -s -f $(SLIBC_LIB_CPP_SO) $(SLIBC_LIB_CPP_SONAME)
	ln -s -f $(SLIBC_LIB_CPP_SONAME) lib$(SLIBC_NAME_CPP).so

%_cpp.o: %.c
	$(CXX) $(CXXFLAGS) -c -o $@ $<
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean: 
	rm -f *.o *.gcda *.gcno *.gcov $(SLIBC_LIB) $(SLIBC_LIB_CPP) \
	$(SLIBC_LIB_SO) $(SLIBC_LIB_CPP_SO)  $(SLIBC_LIB_SONAME) lib$(SLIBC_NAME).so \
	 $(SLIBC_LIB_CPP_SONAME) lib$(SLIBC_NAME_CPP).so
