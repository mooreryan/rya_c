/**
 * @file
 * @author Ryan Moore
 * @brief I'm the header for the Rya library.
 */

#ifndef _RYA_H
#define _RYA_H

#include <stdlib.h>

#define RYA_VERSION_MAJOR @RYA_VERSION_MAJOR@
#define RYA_VERSION_MINOR @RYA_VERSION_MINOR@
#define RYA_VERSION_PATCH @RYA_VERSION_PATCH@
#define RYA_VERSION_STRING "@RYA_VERSION_STRING@"


// CMake checks for certain heaeders
#cmakedefine HAVE_STDARG_H
#cmakedefine HAVE_STDINT_H
#cmakedefine HAVE_SYS_STAT_H

// CMake checks for certain functions
#cmakedefine HAVE_STRNLEN
#cmakedefine HAVE_STRNDUP

#cmakedefine HAVE_VA_COPY
#cmakedefine HAVE_VSNPRINTF


// Some useful constants
#define RYA_OKAY_INT 1
#define RYA_ERROR_INT -10
#define RYA_ERROR_PTR NULL

/**
 * @brief Return type for rya functions that seem like they should be true or false.
 *
 * Since errors are mapped to RYA_ERROR_INT you shouldn't just say `if (val)`, you need to say, `if (val == rya_true)`.  Or, you need to first check for errors, then treat it like a regular true/false value.
 */
enum rya_bool_enum
{
  rya_false = 0, rya_true = 1, rya_error = RYA_ERROR_INT
};
typedef enum rya_bool_enum rya_bool;

// Standarized numeric types
#ifdef HAVE_STDINT_H
#include <stdint.h>

typedef int32_t rya_int;
typedef int64_t rya_long;
#else
typedef int  rya_int;
typedef long rya_long;
#endif

// Macro definitions to follow.

/**
 * @brief Like free, but better.  It sets the ptr to NULL.
 */
#define rya_free(ptr) { free(ptr); (ptr) = 0; }

#ifndef HAVE_VA_COPY
#define va_copy(dest, src) dest = src
#endif

#endif // _RYA_H
