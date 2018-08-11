/**
 * @file
 * @author Ryan Moore
 * @brief I contain file related functions for the Rya library.
 */

#include "rya.h"
#include "rya_file.h"

#include <stdlib.h>
#include <sys/stat.h>

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
rya_bool rya_file_exist(const char* fname)
{
  if (fname == NULL) { return rya_error; }

  struct stat st;

  if (stat(fname, &st) < 0) {
    return rya_false;
  }
  else {
    return rya_true;
  }
}