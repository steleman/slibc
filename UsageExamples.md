# Usage examples #
Here, we will give some sample usage scenarios.

## Alternative for strcpy ##
### Insecure code example ###
```
char str1[10];
strcpy(str1, "LOOOOONNNNNNNNNNNNNNNNNG"); // causes a buffer overflow
```

### Replacement ###
```
errno_t strcpy_s(char *s1,rsize_t s1max,const char *s2)
```

  * allows specifying the size of destination buffer `s1`
  * writes at maximum `s1max-1` bytes and will always terminate `s1` with a 0-byte.
  * If the buffer is too small
    * the constraint handler is called
    * `s1[0]` is set to '\0' if `s1!=NULL` and `s1max >0`

### Secure code example ###
```
char str1[10];
strcpy_s(str1, sizeof(str1), "LOOOOONNNNNNNNNNNNNNNNNG"); 
//no buffer overflow, instead constraint handler will be called, str1[0] set to '\0'
```

## Alternative for strncpy ##
### Insecure code example ###
```
char buf[10]; 
strncpy(buf, "123", strlen("123")); //will leave buf without a terminating null byte
```
The drawback of `strncpy` is that the resulting string might not terminated by a 0-byte. Correct code has to explicitly set the 0-byte. Would it not be better to include that operation into the function itself?

### Replacement ###
```
errno_t strncpy_s(char *s1, rsize_t s1max, const char *s2, rsize_t n);
```

  * allows specifying the size of destination buffer `s1`
  * **allows additionally specifying the number of characters to be copied from the source**
  * writes at maximum `s1max-1` bytes and will always terminate `s1` with a 0-byte.
  * If the buffer is too small
    * the constraint handler is called
    * `s1[0]` is set to '\0' if `s1!=NULL` and `s1max >0`

### Secure code example ###
```
char str1[10];

strncpy_s(str1, sizeof(str1), "loooong string", 3);
// OK, str1 == "lan"

strncpy_s(str1,sizeof(str1),"123456789A",strlen("123456789A"));
// constraint handler will be called, str[0]==0

strncpy_s(str1, sizeof(str1), "loooong string",  sizeof(str1)-1);
// string will be truncated according to the buffer length, str1 is 0-terminated

strncpy_s(str1, sizeof(str1), "String", 10);
//str1 == "String"

strncpy_s(NULL, sizeof(str1), "looong String", 3);
// constraint handler will be called, str1[0] will NOT be set to '\0'
```