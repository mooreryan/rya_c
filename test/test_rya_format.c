#include "unity.h"
#include "rya_format.h"
#include <assert.h>
#include <string.h>

#include <stdlib.h>

/*
 *
 * You can use these fake vsnprintf functions to make sure everything works even if you have wonky vsnprtinf implementations.
 *

int fake_vsnprintf(char * restrict str,
                   size_t size,
                   const char * restrict format,
                   va_list ap)
{
  fprintf(stderr, "WARN -- I'm using fake_vsnprintf().  Do you have debug mode set?\n");

  vsnprintf(str, size, format, ap);

  return -1;
}

int fake_vsnprintf2(char * restrict str,
                   size_t size,
                   const char * restrict format,
                   va_list ap)
{
  fprintf(stderr, "WARN -- I'm using fake_vsnprintf2().  Do you have debug mode set?\n");

  vsnprintf(str, size, format, ap);

  return size - 1;
}

#define vsnprintf fake_vsnprintf2
*/

void setUp(void)
{
}

void tearDown(void)
{
}

void test___rya_asprintf___should_ReturnAPtrWithFormattedString(void)
{
  char* str = NULL;

  char* expected = "Hello, ryan and amelia.  I'm a string that is a whole lot longer than 64 chars (which is the default of this function) so that I can get a couple of iterations through the algorithm.";

  char* fmt = "Hello, %s and %s.  I'm a string that is a whole lot longer than 64 chars (which is the default of this function) so that I can get a couple of iterations through the algorithm.";

  int retval = rya_asprintf(&str, fmt, "ryan", "amelia");

  TEST_ASSERT_EQUAL_STRING(expected, str);

  // I also return the number of chars printed.
  TEST_ASSERT_EQUAL(strlen(expected), retval);

  free(str);
}

void test___rya_asprintf___should_HandleWeirdStuff(void)
{
  char* str = NULL;

  int retval = rya_asprintf(&str, "");
  TEST_ASSERT_EQUAL(0, retval);
  free(str); str = NULL;

  retval = rya_asprintf(&str, "", "apple", "pie");
  TEST_ASSERT_EQUAL(0, retval);
  free(str); str = NULL;

  retval = rya_asprintf(&str, "%s", "");
  TEST_ASSERT_EQUAL(0, retval);
  free(str); str = NULL;

  retval = rya_asprintf(&str, "%s", "apple", "pie");
  TEST_ASSERT_EQUAL(5, retval);
  free(str); str = NULL;
}

void test___rya_format___should_ReturnCharStars(void)
{
  char* expected = "Hi my name is Ryan and I like to code in C.";
  char* fmt = "Hi my name is %s and I like to code in %s.";

  char* actual = rya_format(fmt, "Ryan", "C");

  TEST_ASSERT_EQUAL_STRING(expected, actual);

  free(actual);
}

void test___rya_format___should_ReturnEmptyString(void)
{
  char* actual = rya_format("%s", "");

  TEST_ASSERT_EQUAL_STRING("", actual);

  free(actual);

  actual = rya_format("");
  TEST_ASSERT_EQUAL_STRING("", actual);
}