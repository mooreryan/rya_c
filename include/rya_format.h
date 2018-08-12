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

int rya_vasprintf(char** str, const char* fmt, va_list args);

int rya_asprintf(char** str, const char* fmt, ...);

char* rya_format(const char* fmt, ...);

#endif


#endif // _RYA_FORMAT_H
