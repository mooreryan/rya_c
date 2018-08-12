/**
 * @file
 * @author Ryan Moore
 * @brief I'm the header for format related functions for the Rya library.
 */

#ifndef _RYA_FORMAT_H
#define _RYA_FORMAT_H

#include <stdarg.h>

/*
// 1. Need to check for stdarg.h and va_copy.  va_copy because va_list might have pointers to other things and need to be deep copied as vsnprintf may modify contents of va_list.

In this case you'll want to do something like
 #ifndef va_copy
#define va_copy(dest, src) dest = src
#endif

 It will only do shallow copies though, so it'll blow up if you need a deep copy.

 2. You'll also need vsnprintf

 Some implementations of vsnprintf always return -1 on error.  Some return the value of what what the length would have been if the buffer were large enough (e.g., C99 compliant).

 Oh and you'll want to check that your input for size is < INT_MAX as some implementations have: The size argument exceeds INT_MAX + 1, or the return
			value would be too large to be represented by an int.


 Oh and you'll want to check if your output size overflows.  vsnprintf return int's and on the C99 compliant ones will tell you the length required if your buffer was too small.  Anyway, you should check the output for < INT_MAX.

 Another consideration is if there is a failure, there are no guarantees about how much data was written to the buffer (I think).  So you'd need to somehow track that...maybe memset the string to '?' or something.
*/

int rya_vasprintf(char** str, const char* fmt, va_list args);

int rya_asprintf(char** str, const char* fmt, ...);

char* rya_format(const char* fmt, ...);

#endif // _RYA_FORMAT_H
