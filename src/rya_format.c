/**
 * @file
 * @author Ryan Moore
 * @brief I contain format related functions for the Rya library.
 */

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>
#include <errno.h>

#include "rya.h"
#include "rya_format.h"

#ifdef HAVE_VSNPRINTF

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
int rya_asprintf(char** str, const char* fmt, ...)
{
  int num_chars = 0;

  va_list args;

  va_start(args, fmt);
  num_chars = rya_vasprintf(str, fmt, args);
  va_end(args);

  return num_chars;
}

/**
 * @brief Format strings but nice.
 * @note Uses rya_vasprintf() internally, so see the notes and warnings there.
 * @note I will only be defined if HAVE_VSNPRINTF is set.

 * @param fmt
 * @param ...
 * @retval RYA_ERROR_PTR on errors
 * @retval the formatted string
 */
char* rya_format(const char* fmt, ...)
{
  char* str = NULL;
  int num_chars = 0;

  va_list args;

  va_start(args, fmt);
  num_chars = rya_vasprintf(&str, fmt, args);
  va_end(args);

  if (num_chars == -1 || str == NULL) { return RYA_ERROR_PTR; }

  return str;
}


/*
  A quote from better string library comments....  On IRIX vsnprintf
  returns n-1 when the operation would overflow the target buffer,
  WATCOM and MSVC both return -1, while C99 requires that the returned
  value be exactly what the length would be if the buffer would be large
  enough.
*/

// TODO does buffer ever need to be free'd?
// TODO warn when more or less args than format specifiers.

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
int rya_vasprintf(char** str_ptr, const char* format, va_list args)
{
  size_t str_len     = 0;
  int    buffer_size = 15; // size of 4 32 bit ints by default
  assert(buffer_size > 0);
  char* buffer = NULL;

  do {
    errno = 0;
    *str_ptr = (char*)realloc(buffer, (size_t)buffer_size);
    if (*str_ptr == NULL) {
      rya_free(buffer);
      return -1;
    } // else, *str_ptr will be allocated and buffer will be de-allocated

    // now nearly all the chars are non-null, we'll need this to check later.
    memset(*str_ptr, '?', (size_t)buffer_size - 1);
    // Set the last char to nul so it's valid.
    (*str_ptr)[buffer_size - 1] = '\0';

    // If we're on a platform where this is a deep copy, that's good.
    // If not, hope that you don't have args that require deep copying
    // as vsnprintf isn't guaranteed not to change things.
    va_list args_copy;
    va_copy(args_copy, args);
    errno = 0;
    vsnprintf(*str_ptr, buffer_size, format, args_copy);

    // An invalid wide character code was encountered.
    if (errno == EILSEQ) {
      rya_free(*str_ptr);
      return -1;
    }
    // Insufficient storage space is available.
    if (errno == ENOMEM) {
      rya_free(*str_ptr);
      return -1;
    }

    va_end(args_copy);

    // We can't actually trust the return value of vsnprintf.  So we
    // hack it.  We know vsnprintf() nul terminates at the
    // buffer_size'th position in the buffer.  So if we find the nul
    // char before the size of the buffer we know it was at least sort
    // of successful.

#ifdef HAVE_STRNLEN
    str_len = strnlen(*str_ptr, (size_t)buffer_size);
#else
    str_len = strlen(*str_ptr);
#endif


    // We know that vsnprintf always null terminates.  Now if str_len
    // < buffer_size, we know that vsnprintf null terminated it as we
    // memset the buffer to '?' and put the null terminator at
    // buffer_size'th index.  If for some reason, vsnprintf on error
    // puts a null char in the buffer somewhere before buffer size,
    // the result won't be what you want possibly, but it won't be
    // invalid as it will fit inside of str_ptr properly.
    if (str_len >= INT_MAX) {
      // Something def went wrong here and our buffer_size was too big.
      rya_free(*str_ptr);
      return -1;
    }
    else if (str_len < (size_t)buffer_size - 1) {
      // (v)snprintf functions should return the number of chars
      // written on success.
      return (int)str_len;
    }
    else {
      // The buffer was NOT big enough to hold the result.  Double the
      // buffer size and try again.
      // Do it this wonky way so we'll hit INT_MAX exactly.
      buffer_size = (buffer_size + 1) * 2 - 1;

      buffer = *str_ptr; // and reset the buffer
    }
  } while (buffer_size <= INT_MAX);
  // My 64 bit machine int max is 2,147,483,647.  If starting buffer
  // size is 16, this check will fail after completing the 27th
  // iteration.  So if you've got some weird case where you keep
  // getting memory errors or EILSEQ errors, this will just return
  // with a -1 and free the first arg, after iterating 27 times.  (2gb
  // max allocation on the last iteration)

  // If you get all the way here, there was an error.
  rya_free(*str_ptr);
  return -1;
}
#endif
