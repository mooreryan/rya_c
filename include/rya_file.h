/**
 * @file
 * @author Ryan Moore
 * @brief I'm the header for the file functions.
 */

#ifndef _RYA_FILE_H
#define _RYA_FILE_H

#include "rya.h"

#ifdef HAVE_SYS_STAT_H

/**
 * @brief I tell whether a file exists or not.
 *
 * Basically I'm a wrapper to stat().
 *
 * @param fname
 * @retval rya_error if fname is NULL
 * @retval rya_false if the file does NOT exist
 * @retval rya_true if the file exists
 */
rya_bool rya_file_exist(const char* fname);

#endif

#endif // _RYA_FILE_H
