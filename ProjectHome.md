# Introduction #
This library provides an implementation of the bounds-checking C functions (as specified in Annex K of the current C standard, a.k.a. C11) for **use with the GNU C library**. These functions lower the risk of introducing security vulnerabilities such as buffer overflows and format string vulnerabilities into your code by providing clear and easy-to-use interfaces. For each C function a secure alternate function ending in a `"_s"` postfix is provided (e.g., `strcpy_s`). Use of these functions is recommended by security experts and secure coding standards ([CERT Secure Coding Standard C](https://www.securecoding.cert.org/confluence/display/seccode/STR07-C.+Use+the+bounds-checking+interfaces+for+remediation+of+existing+string+manipulation+code)).

# News #

ALL Downloads have moved to Google Drive, you can find them [here](https://drive.google.com/folderview?id=0B5nfJ2V9i6UTQ2tjM3laTWhwMm8&usp=drive_web)

## Latest Release ##
  * Jul 20, 2014: Slibc 0.9.3 released
[Download](https://drive.google.com/folderview?id=0B5nfJ2V9i6UTQ2tjM3laTWhwMm8&usp=drive_web) | [Introduction to Slibc](SlibcIntroduction.md) | [API documentation](https://slibc.googlecode.com/svn/api-doc/html/index.html)

For a quick overview of the changes in the latest version, have a look at the [Changelog](Changelog.md)

# Repositories #
Repositories for OpenSuSE, SuSE Linux Enterprise, CentOS, Red Hat Enterprise, Fedora, Debian and Ubuntu are available [here](https://build.opensuse.org/package/repositories/home:SecureBusinessAustria:slibc/slibc). Please select the corresponding repository for your distribution and add it to your package manager. If you are running an OBS supported version of a distribution, that we haven't added, please contact us and we'll do our best to add it as well.

# Motivation #

Consider the following code and ask yourself which of the following operations are correct in the sense that they do not cause a buffer overflow or leave a string without a terminating null byte.
```
char buf[10]; 
strncpy(buf, "123", strlen("123")); //will leave buf without a terminating null byte
strncpy(buf, "123", sizeof(buf);    //in this case correct
strncpy(buf, "123456789A", 9);      //will leave buf without a terminating null byte
memset(buf, '\0', sizeof(buf));    
strncat(buf, "123456789A", sizeof(buf)); // buffer overflow because strncat always adds a terminating null byte
```

Would it not be easier if you had the possibility to specify the size of a target buffer and not worry that the implementation will overwrite memory?
This is what this library and their `_s` functions are for.

```
char buf[10]; 
strcpy_s(buf, sizeof(buf), "123");
strcpy_s(buf, sizeof(buf), "123");
strcpy_s(buf, sizeof(buf), "123456789A"); //buf is not big enough, thus no copying will take place
memset_s(buf, sizeof(buf), '\0', sizeof(buf));    
strcat_s(buf, sizeof(buf), "123456789A");  //buf is not big enough, thus no copying will take place
```

# Implementation #

This library consists of
  * a **thread-safe** implementation of all functions specified in the ISO Standard (except widechar functions)
  * [API documentation](https://slibc.googlecode.com/svn/api-doc/html/index.html) for all functions
  * test cases for all functions
  * overloaded C++ template functions for easier use when compiling with g++


# About #
Slibc was implemented by the SSG team of [SBA Research, Austria](http://www.sba-research.org/). The main contributors of this project are Ulrich Bayer (ubayer@sba-research.org) and Peter  Aufner (paufner@sba-research.org).
