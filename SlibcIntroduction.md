# Introduction #
Slibc provides an implementation of the C11 "Bounds-checking Interfaces". The specification adds 68 new functions to the C library, which can be easily recognized by having a `_s` postfix in their names.
One of the ideas behind the development of these new functions was to reduce the likelihood of buffer overflows by making buffer sizes explicit. Every function in the C standard
that accepts an array argument is complemented by a corresponding `_s` counterpart.


For example,a function
```
errno_t strcpy_s(char *s1,rsize_t s1max,const char *s2)
```
was added. This new function
behaves similarly to the traditional `strcpy` but it requires the caller to supply the size of the destination buffer in parameter `s1max`. Provided that the caller supplies the correct buffer
size, the function, thus, has the possibility to avoid writing outside allocated buffer boundaries. Instead of writing outside buffer boundaries, `strcpy_s` returns an error in its return value and
additionally invokes the so-called constraint handler. This is a user-configurable callback function,
which by default terminates the process.


# How to use the library #
## Installation ##
  1. Download the package from the Downloads page.
  1. Extract it.
  1. Compile the slibc libary by typing `make`. At the moment two static libraries are created: `libslibc.a` and `libslibc++.a` . The latter is compiled with a C++ compiler. If you are developping a C++ application we recommend using the C++ version.
  1. Optionally run all tests by executing `make test`.

## Use SLIBC with your program ##

  1. Use the new `_s` functions in your code:
```
#include <string.h>
int main(int argc, char *argv[])
{
	char dest[10];	
	strcpy_s(dest, sizeof(dest), argv[0]);
}
```
  1. When compiling include the SLIBC header directory (`include/slibc`) in your compiler's include path (e.g., add `-I~/slibc/include/slibc`). Remember that Annex K adds functions to the standard C library by extending existing header files. SLIBC makes the fact that it's a third-party library (instead of being part of GLIBC) as transparent as possible to your program. To use `strcpy_s`, simply include `string.h` in your program. It is important that your compiler searches in the slibc header directory first.
  1. Link your program to Slibc. Slibc is built as a shared library. Either add `-lslibc` or `-lslibc++` (for the C++ version) to your linking step. Additionally, you might have to add the location of slibc's so-files to your  Linker search path by adding `-L` (e.g., `-L../src/`).
  1. Run your program. If the Slibc shared object file cannot be found, you have to adjust the environment variable `LD_LIBRARY_PATH`.


# Concepts behind SLIBC #

## Runtime contraint violations ##
Each new `_s` function performs as many checks as possible on supplied arguments.
  * All pointers are checked for being different from NULL,
  * all buffer sizes are checked for being large enough before writing to them,
  * etc.

The C standard calls these argument checks **runtime constraints**. In case they are violated, a constraint handler is called before the function returns. The constraint handler is a user-configurable call-back function. The standard foresees two standard handler implementations:
  * `abort_handler_s` for terminating the program upon a constraint violation and the
  * `ignore_handler_s` for ignoring all invocations of the constraint handler.
By default (if unset), the `abort_handler_s` is active in the SLIBC implementation.

For more information, see [CERT C Secure Coding Standard:  API00-C. Functions should validate their parameters](https://www.securecoding.cert.org/confluence/display/seccode/API00-C.+Functions+should+validate+their+parameters)

## Specify a buffer size for all buffer arguments ##
By specifying buffer sizes for all buffer arguments, the `_s` functions can check whether the supplied buffer arguments are big enough before overflowing memory.

See also [CERT C Secure Coding Standard:  Functions that read or write to or from an array should take an argument to specify the source or target size](https://www.securecoding.cert.org/confluence/display/seccode/API02-C.+Functions+that+read+or+write+to+or+from+an+array+should+take+an+argument+to+specify+the+source+or+target+size)

## Do not mix data with error indicators ##
Many of the new functions explicitly return error codes as a type `errno_t`. This means they only return an error code or the special value 0 if no error occured. This is simple to use and easy to understand. Traditional functions often try to pack too much information into the return value (e.g., `sprintf`) giving rise to subtle bugs.

See [CERT C++ Secure Coding Standard: ERR02-CPP. Avoid in-band error indicators](https://www.securecoding.cert.org/confluence/display/cplusplus/ERR02-CPP.+Avoid+in-band+error+indicators) for more information.

## Forbid rarely needed but dangerous constructs ##
To decrease the consequences of format string vulnerabilities, the `%n` conversion specifier is not allowed in the format string arguments accepted by the `printf_s` family of functions. The `%n` flag is dangerous because it allows an attacker to **write** to memory regions while being hardly used by legitimate programs.