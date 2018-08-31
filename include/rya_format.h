/**
 * @file
 * @author Ryan Moore
 * @brief I'm the header for format related functions for the Rya library.
 */

#ifndef _RYA_FORMAT_H
#define _RYA_FORMAT_H

#include <stdarg.h>
#include "rya.h"

#if defined(HAVE_STDARG_H) && defined(HAVE_VSNPRINTF)

/**
 * @brief More or less a drop-in replacement for vasprintf(), except that it should work regardless of whether or not the vsnprintf() implementation is broken.
 *
 * Will set errno...
 *
 * ~~~
 * | Value  | Meaning                                         |
 * |--------|-------------------------------------------------|
 * | ENOMEM | Insufficient storage space is available.        |
 * | EILSEQ | An invalid wide character code was encountered. |
 * ~~~
 *
 * @param str_ptr
 * @param format
 * @param args
 * @retval -1 on errors
 * @retval the number of chars written minus the terminating null char.
 *
 * @todo I don't warn when there are more or fewer args than format specifiers.
 * @todo Should I free the buffer as well?
 *
 * @note For more info, see the implementation of bformat() from the better string library and also this blog entry: http://insanecoding.blogspot.com/2014/06/memory-management-in-c-and-auto.html.
 * @note I will only be defined if HAVE_VSNPRINTF is set.
 *
 * @warning About shallow copies...If your platform doesn't have a va_copy that does deep copies, we use a defined shallow copy version.  If you have args that require deep copying, then this will be a problem for you.
 */
int rya_vasprintf(char** str_ptr, const char* format, va_list args);

/**
 * @brief More or less a drop-in replacement for asprintf(), except that it should work regardless of whether or not the vsnprintf() implementation is broken.
 *
 * @note I will only be defined if HAVE_VSNPRINTF is set.
 * @param str
 * @param fmt
 * @param ...
 * @retval -1 on errors
 * @retval the number of chars written minus the terminating null char.
 */
int rya_asprintf(char** str, const char* fmt, ...);

/**
 * @brief Format strings but nice.
 * @note Uses rya_vasprintf() internally, so see the notes and warnings there.
 * @note I will only be defined if HAVE_VSNPRINTF is set.

 * @param fmt
 * @param ...
 * @retval RYA_ERROR_PTR on errors
 * @retval the formatted string
 */
char* rya_format(const char* fmt, ...);

#endif


#endif // _RYA_FORMAT_H
