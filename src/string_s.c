/* Copyright (C) 2011-2012 SBA Research gGmbh

   This file is part of the Slibc Library.

   The Slibc Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The Slibc library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the Slibc Library; if not, see
   <http://www.gnu.org/licenses/>.  
*/
//Request the glibc-spcific strerror_r function
#ifndef _GNU_SOURCE
# define _GNU_SOURCE
#endif
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/file.h>

#include "slibc.h"
#include <unistd.h>

// external declaration
char *
gnu_strtok_s(char * restrict s1,
			 rsize_t * restrict s1max,
			 const char * restrict s2,
			 char ** restrict ptr);

// ** Implementation **



size_t strnlen_s(const char *s, size_t maxsize)
{
	if (!s) return 0;

	return strnlen(s, maxsize);
}


errno_t strcpy_s(char * restrict s1, rsize_t s1max, const char * restrict s2)
{
	if (!s1 || s1max == 0 || s1max > RSIZE_MAX )
	{
		RUNTIME_CONSTRAINT_HANDLER();
		return EINVAL;
	}

	rsize_t s2_len = 0;
	if (!s2 || s1max <= (s2_len=strnlen_s(s2, s1max)) )
	{
		s1[0] = 0;
		RUNTIME_CONSTRAINT_HANDLER();
		return EINVAL;
	}
	
	// Check whether s1 and s2 overlap
	if (REGIONS_OVERLAP_CHECK(s1, s1max, s2, s2_len+1))
	{
		s1[0] = 0;
		RUNTIME_CONSTRAINT_HANDLER();
		return EINVAL;
	}

	strncpy(s1, s2, s1max-1);
	s1[s1max-1] = '\0';

	// on success
	return 0;
}


errno_t strncpy_s(char * restrict s1, rsize_t s1max, const char * restrict s2, rsize_t n)
{
	rsize_t m;

	if (!s1 || s1max == 0 || s1max > RSIZE_MAX)
	{
		RUNTIME_CONSTRAINT_HANDLER();
		return EINVAL;
	}

	if ( !s2 ||	 n > RSIZE_MAX || (n >= s1max && s1max <= strnlen_s(s2, s1max)) )
	{
		s1[0] = 0;
		RUNTIME_CONSTRAINT_HANDLER();
		return EINVAL;
	}
	
	if (REGIONS_OVERLAP_CHECK(s1, s1max, s2, n+1))			 
	{
		s1[0] = 0;
		RUNTIME_CONSTRAINT_HANDLER();
		return EINVAL;
	}

	m = MIN(n, s1max-1);
	strncpy(s1, s2, m);
	s1[MIN(n, s1max-1)] = '\0';

	// on success
	return 0;
}



errno_t strcat_s(char * restrict s1,
				 rsize_t s1max,
				 const char * restrict s2)
{
	if (!s1 || s1max == 0 || s1max > RSIZE_MAX)
	{
		RUNTIME_CONSTRAINT_HANDLER();
		return EINVAL;
	}

	size_t s1_len = 0;
	rsize_t s2_len = 0;
	size_t m = s1max - (s1_len=strnlen_s(s1, s1max));

	if ( !s2 || m == 0 || (m <= (s2_len=strnlen_s(s2, m))) )
	{
		s1[0] = 0;
		RUNTIME_CONSTRAINT_HANDLER();
		return EINVAL;
	}
	
	if (REGIONS_OVERLAP_CHECK(s1+s1_len, m, s2, s2_len+1)) 
	{
		s1[0] = 0;
		RUNTIME_CONSTRAINT_HANDLER();
		return EINVAL;
	}

	strncat(s1, s2, m-1);
	// should not be necessary
	s1[s1max-1] = '\0';
	
	return 0;
}


errno_t strncat_s(char * restrict s1,
				  rsize_t s1max,
				  const char * restrict s2,
				  rsize_t n)
{
	if (!s1 || s1max == 0 || s1max > RSIZE_MAX)
	{
		RUNTIME_CONSTRAINT_HANDLER();
		return EINVAL;
	}

	size_t s1_len = 0;
	size_t m = s1max - (s1_len=strnlen_s(s1, s1max));

	if ( !s2 || n > RSIZE_MAX || m == 0 || (n >= m && m <= strnlen_s(s2, m)) )
	{
		s1[0] = 0;
		RUNTIME_CONSTRAINT_HANDLER();
		return EINVAL;
	}
	
	if (REGIONS_OVERLAP_CHECK(s1+s1_len, m, s2, n+1)) 
	{
		s1[0] = 0;
		RUNTIME_CONSTRAINT_HANDLER();
		return EINVAL;
	}

	strncat(s1, s2, m-1);
	// should not be necessary
	s1[s1max-1] = '\0';
	
	return 0;
}

errno_t memcpy_s(void * restrict s1, rsize_t s1max,
				 const void * restrict s2, rsize_t n)
{
	if(!s1 || !s2 || s1max > RSIZE_MAX || n > RSIZE_MAX || n > s1max || 
	   REGIONS_OVERLAP_CHECK(s1, s1max, s2, n))
	{
		if(s1 != (void *) NULL && s1max <= RSIZE_MAX)
			memset(s1, 0, s1max);

		RUNTIME_CONSTRAINT_HANDLER();
		return EINVAL;
	}
	void * res = memcpy(s1, s2, n);
	if (res != (void *) NULL)
		return 0;
	return -1;
}

errno_t memmove_s(void *s1, rsize_t s1max,
				  const void *s2, rsize_t n)
{
	if(!s1 || !s2 || s1max > RSIZE_MAX || n > RSIZE_MAX || n > s1max)
	{
		if(s1 != (void *) NULL && s1max <= RSIZE_MAX)
			memset(s1, 0, s1max);

		RUNTIME_CONSTRAINT_HANDLER();
		return EINVAL;
	}
	
	(void) memmove(s1,s2,n);

	return 0;
}

char *strtok_s(char * restrict s1,
			   rsize_t * restrict s1max,
			   const char * restrict s2,
			   char ** restrict ptr)
{
	if(!s1max || !s2 || !ptr || (!s1 && !*ptr) || *s1max > RSIZE_MAX)
	{
		RUNTIME_CONSTRAINT_HANDLER();
		return (char *) NULL;
	}
	return gnu_strtok_s(s1, s1max, s2, ptr);
}

errno_t strerror_s(char *s, rsize_t maxsize,
				   errno_t errnum)
{
	if(!s || maxsize > RSIZE_MAX || maxsize == 0)
	{
		RUNTIME_CONSTRAINT_HANDLER();
		return EINVAL;
	}

#ifdef SLIBC_MT
	// this version is thread-safe

	// we use the GNU strerror_r instead of the XSI-compliant strerror_r
	// the XSI-compliant strerror_r returns an error if the buffer
	// is not big enough. For our purposed, truncate behavior is better.
	char *err = strerror_r(errnum, s, maxsize);
	if (err != s)
	{
		// in that case strerror_r returned a static string
		// copy it into our buffer
		strncpy_s(s, maxsize, err, maxsize-1);

		// was the message truncated?
		if (strlen(err) > maxsize-1)
		{
			// truncation happened.
			if (maxsize > 3)
				s[maxsize-2] = s[maxsize-3] = s[maxsize-4] = '.';

			return -1;
		}
		return 0;
	}
	else
	{
		// the result was already copied into s

		if (strlen(s) == maxsize-1)
		{
			// the error string takes up all of the available space
			// we do not know whether the string was truncated.
			// find that out
			char *tmp = (char*) malloc(maxsize + 1);
			// we try with one additional byte
			char *ret = strerror_r(errnum, tmp, maxsize+1);
			if (strlen(ret) > strlen(s))
			{
				// truncation happened
				if (maxsize > 3)
					s[maxsize-2] = s[maxsize-3] = s[maxsize-4] = '.';	
				free(tmp);
				return -1;
			}
			free(tmp);
			return 0;
		}
		return 0;
	}
#else
	// not thread-safe, but simpler
	char * ch = strerror(errnum);
	strcpy_s(s, maxsize, ch);


	if(strlen(ch) < maxsize)
	{
		strncpy(s, ch, maxsize-1);
		s[maxsize-1] = '\0';
		return 0;
	} else {
		strncpy(s, ch, maxsize-1);
		if(maxsize > 3)
		{
			rsize_t i;
			for(i = maxsize -4; i < maxsize-1; i++)
				s[i] = '.';
		}
		s[maxsize-1] = '\0';
		return -1;
	}
#endif
}

size_t strerrorlen_s(errno_t errnum)
{
	char * ch = strerror(errnum);
	return strlen(ch);
}
