include ../Makefile.inc

.PHONY: all clean

all: $(SLIBC_LIB) $(SLIBC_LIB_CPP) libslibc.so libslibc++.so

SLIBC_OBJS=slibc.o stdio_fmt_s.o string_s.o stdio_s.o stdlib_s.o \
	time_s.o stdio_ext_s.o \
	gnu_qsort_s.o gnu_bsearch_s.o gnu_strtok_s.o gnu_vfscanf_s.o 

SLIBC_OBJS_CPP=slibc_cpp.o stdio_fmt_s_cpp.o string_s_cpp.o stdio_s_cpp.o stdlib_s_cpp.o \
	time_s_cpp.o stdio_ext_s_cpp.o \
	gnu_qsort_s_cpp.o gnu_bsearch_s_cpp.o gnu_strtok_s_cpp.o gnu_vfscanf_s_cpp.o 

$(SLIBC_LIB): $(SLIBC_OBJS)
	ar rcs $(SLIBC_LIB) $(SLIBC_OBJS)

$(SLIBC_LIB_CPP): $(SLIBC_OBJS_CPP)
	ar rcs $(SLIBC_LIB_CPP) $(SLIBC_OBJS_CPP)

libslibc.so: $(SLIBC_OBJS)
	gcc -shared -o libslibc.so $(SLIBC_OBJS)
        
libslibc++.so: $(SLIBC_OBJS_CPP)
	gcc -shared -o libslibc++.so $(SLIBC_OBJS_CPP)

%_cpp.o: %.c
	$(CXX) $(CXXFLAGS) -c -o $@ $<
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean: 
	rm -f *.so *.o *.gcda *.gcno *.gcov $(SLIBC_LIB) $(SLIBC_LIB_CPP)
