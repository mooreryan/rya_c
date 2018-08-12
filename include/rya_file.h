/**
 * @file
 * @author Ryan Moore
 * @brief I'm the header for the file functions.
 */

#ifndef _RYA_FILE_H
#define _RYA_FILE_H

#include "rya.h"

#ifdef HAVE_SYS_STAT_H

rya_bool rya_file_exist(const char* fname);

#endif

#endif // _RYA_FILE_H
