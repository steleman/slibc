# Frequently asked questions #

## Why are the slibc tests written as a C++ program? ##
The decision to use the C++ unit testing framework `cppunit` for our tests has historic reasons.

## Is it necessary to use the new functions for avoiding buffer overflows? ##
No. Consider the following code example. It is correct and uses traditional functions.
```
errno_t function foo(const char *arg)
{
    char buf[10];
	if (strlen(arg) > sizeof(buf) - 1)
	    return EINVAL;
	else
	    strcpy(buf, arg);
  
   //more code ...
}
```
The question is how many `strcpy` invocations have you seen without an appropriate length check of the source buffer?

## What about the existing `n` variant functions? ##

The traditional C functions (including their n variants), such as `strcpy`, `strncpy`, suffer from the following problems:
  * Length checks are tedious and thus not done.
  * Off-by-One errors are common because the calculated size differs by 1 from the real buffer size.
  * Unfortunately, the standard C library is very inconsistent:
    * Do you have to reserve space for the terminating null byte or not?
    * Will the function automatically add a terminating 0-byte (`strcat`) or do you have to do it yourself (`strncpy`)?
    * Does the function accept the number of characters (`strncpy`) or the buffer size (`snprintf`)?
    * What happens if the string is NULL or is not terminated by a '\0' byte?

## Is slibc available under a different license than the GNU LGPL? ##
slibc relies heavily on the GNU C library. In certain cases, it serves as a simple wrapper but in other cases we directly reuse GLIBC's implementation.
Thus, slibc as a whole is only available under the LGPL.

## Does Slibc work with other C libraries than the GNU C library? ##
Certain slibc functions such as `strcpy_s` are simple wrappers around standard C functions. In other cases, it is more difficult and slibc depends on functionality only present in the GNU C library. Moreover, dependencies to GCC exist.

## Are there only advantages to using the bounds-checking interfaces? ##
Many security experts and coding standards [CERT Secure Coding Standard C](https://www.securecoding.cert.org/confluence/display/seccode/STR07-C.+Use+the+bounds-checking+interfaces+for+remediation+of+existing+string+manipulation+code) recommend using the bounds-checking interfaces. Microsoft [Security Enhancements in the CRT](http://msdn.microsoft.com/en-us/library/8ef0s5kh%28v=vs.80%29.aspx) has deprecated traditional C functions such as `strcpy`. The bounds-checking interfaces are definitely an improvement when compared to the traditional C functions. We recommend using the `_s` function wherever you'd normally use a traditional C function. They also serve well as a drop-in replacement for existing code bases. If you compile your C code with g++, have a look at our C++ templates that make the transformation of existing code even easier.

However, the bounds-checking interfaces do not solve all problems for you. Static buffers and bounds-checking are still a not ideal solution in many cases. Often, we'd wish for simple dynamic array handling that grows buffers as needed to accomodate for variable length input. In C, you might want to look for a managed string library such as [CERT Managed String Library](https://www.securecoding.cert.org/confluence/display/seccode/Managed+String+Library) for that purpose. When programming in C++, best use `std::vector` and the standard containers instead of relying on `_s` functions.

Summing up, we see the following advantages, disadvantages and unsolved problems:

### Advantages ###
  * **Reduction of buffer overflows**: Every array argument accepts a size specification. That's a simple design rule that reduces the likelihood of simple buffer overflow errors.
  * **Easy-to-use and consistent interface**: The new functions are easier to use (when writing code), to understand (when learning about them) and to read (when performing code reviews) than the traditional functions.
  * **Very similar to existing functions**: Easy migration possible.
  * **Standards compliant**: All of the `_s` functions are specified in Annex K of the newest C standard published in 2011.
  * **Length checks in the correct place**: It is tedious to determine the source string length on every call to `strcpy`. It makes sense to perform the length check inside the stringcopy function.

### Disadvantages ###
  * **Performance penalty**: Additional checks cost a bit of performance.
  * **New interface**: Although being very similar to existing functions, it is new and one needs to inform oneself first.

### Problems unsolved by slibc ###
  * **Buffer overflows still possible**: Buffer overflows are still possible in other parts of your program or if wrong buffer sizes are supplied.
  * **No dynamic memory**: In the ideal case you do not want to deal with length limitations but allow for inputs of variable length. A dynamic string handling library can give you that. In C++, better use `std::string` and containers such as `std::vector`.
  * **Program termination**: The default behavior of terminating a program in case of a runtime constraint violation is only slightly better than overflowing buffers. A robust program still has to check for error conditions.