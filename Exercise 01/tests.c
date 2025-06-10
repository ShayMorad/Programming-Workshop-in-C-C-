#include "tests.h"
#include <string.h>

#define K_1 3
#define K2 2
#define K3 (-1)
#define K4 (-3)
#define K5 29

// See full documentation in header file
int test_encode_non_cyclic_lower_case_positive_k ()
{
  char in[] = "abc";
  char out[] = "def";
  encode (in, K_1);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_encode_cyclic_lower_case_special_char_positive_k ()
{
  char in[] = "z@yx";
  char out[] = "b@az";
  encode (in, K2);
  return strcmp (in, out) != 0;

}

// See full documentation in header file
int test_encode_non_cyclic_lower_case_special_char_negative_k ()
{
  char in[] = "d@!c";
  char out[] = "c@!b";
  encode (in, K3);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_encode_cyclic_lower_case_negative_k ()
{
  char in[] = "ab";
  char out[] = "xy";
  encode (in, K4);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_encode_cyclic_upper_case_positive_k ()
{
  char in[] = "AB";
  char out[] = "DE";
  encode (in, K5);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_decode_non_cyclic_lower_case_positive_k ()
{
  char in[] = "def";
  char out[] = "abc";
  decode (in, K_1);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_decode_cyclic_lower_case_special_char_positive_k ()
{
  char in[] = "z@yx";
  char out[] = "x@wv";
  decode (in, K2);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_decode_non_cyclic_lower_case_special_char_negative_k ()
{
  char in[] = "c@!b";
  char out[] = "d@!c";
  decode (in, K3);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_decode_cyclic_lower_case_negative_k ()
{
  char in[] = "de";
  char out[] = "gh";
  decode (in, K4);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_decode_cyclic_upper_case_positive_k ()
{
  char out[] = "AB";
  char in[] = "XY";
  encode (in, K5);
  return strcmp (in, out) != 0;
}
