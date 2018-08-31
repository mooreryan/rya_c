/**
 * @file
 * @author Ryan Moore
 * @brief I contain file related functions for the Rya library.
 */

#include <stdlib.h>

#include "rya.h"
#include "rya_file.h"

#ifdef HAVE_SYS_STAT_H
#include <sys/stat.h>

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

#endif