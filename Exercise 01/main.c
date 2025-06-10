#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "cipher.h"
#include "tests.h"
#include <ctype.h>

#define LINE_LENGTH 1026
#define TEST_ARGS 2
#define RUN_ARGS 5
#define BASE_K 10
#define COMMAND_INDEX 1
#define K_INDEX 2
#define INPUT_INDEX 3
#define OUTPUT_INDEX 4

/**
 * A simple program to encode/decode strings.
 * Encodes/decodes only characters from A-Z and a-z.
 * @return 0 upon success.
 */


/**
 * Runs varius tests on a given command input "test" to the program.
 * @return 0 upon success.
 */
int check_tests (void);

/**
 * Checks if the 'k' shift value is legal.
 * @return 0 upon success.
 */
int check_k (const char *argv);

/**
 * Runs encode/decode based on input command.
 * @return 0 upon success.
 */
int cipher (char *argv[], long k);

int main (int argc, char *argv[])
{
  if ((TEST_ARGS != argc) && (argc != RUN_ARGS))
  {
    fprintf (stderr, "The program receives 1 or 4 arguments only.\n");
    return EXIT_FAILURE;
  }

  if (argc == TEST_ARGS)
  {
    if (strcmp (argv[COMMAND_INDEX], "test") == 0)
    {
      return check_tests ();
    }
    else
    {
      fprintf (stderr, "Usage: cipher test\n");
      return EXIT_FAILURE;
    }
  }
  else if (argc == RUN_ARGS)
  {
    if ((strcmp (argv[COMMAND_INDEX], "decode") != 0) &&
        (strcmp (argv[COMMAND_INDEX], "encode") != 0))
    {
      fprintf (stderr, "The given command is invalid.\n");
      return EXIT_FAILURE;
    }
    else
    {
      int check_k1 = check_k (argv[K_INDEX]);
      if (check_k1 == EXIT_FAILURE)
      {
        fprintf (stderr, "The given shift value is invalid.\n");
        return EXIT_FAILURE;
      }
      long k = strtol (argv[K_INDEX], NULL, BASE_K);
      return cipher (argv, k);
    }
  }
}

//Check documentation on function declare above.
int check_k (const char *argv)
{
  char s = argv[0];
  int i = 0;
  if (s == '-')
  {
    s = argv[1];
  }
  if (!isdigit(s))
  {
    return EXIT_FAILURE;
  }
  while (s != '\0')
  {
    if (!isdigit(s))
    {
      return EXIT_FAILURE;
    }
    i++;
    s = argv[i];
  }

  return EXIT_SUCCESS;
}

//Check documentation on function declare above.
int cipher (char *argv[], long k)
{
  FILE *input = fopen (argv[INPUT_INDEX], "r");
  FILE *output = fopen (argv[OUTPUT_INDEX], "w");
  if ((input == NULL) || (output == NULL))
  {
    if (input == NULL)
    {
      fprintf (stderr, "The given file is invalid.\n");
      return EXIT_FAILURE;
    }
    else
    {
      fclose (input);
      fprintf (stderr, "The given file is invalid.\n");
      return EXIT_FAILURE;
    }
  }
  char input_line[LINE_LENGTH];
  while (fgets (input_line, LINE_LENGTH, input) != NULL)
  {
    if (strcmp (argv[COMMAND_INDEX], "decode") == 0)
    {
      decode (input_line, k);
      fprintf (output, "%s", input_line);
    }
    else if (strcmp (argv[COMMAND_INDEX], "encode") == 0)
    {
      encode (input_line, k);
      fprintf (output, "%s", input_line);
    }
  }
  fclose (input);
  fclose (output);
  return EXIT_SUCCESS;
}

//Check documentation on function declare above.
int check_tests ()
{
  if (test_encode_non_cyclic_lower_case_positive_k () != 0)
  {
    return EXIT_FAILURE;
  }
  if (test_encode_cyclic_lower_case_special_char_positive_k () != 0)
  {
    return EXIT_FAILURE;
  }
  if (test_encode_non_cyclic_lower_case_special_char_negative_k () != 0)
  {
    return EXIT_FAILURE;
  }
  if (test_encode_cyclic_lower_case_negative_k () != 0)
  {
    return EXIT_FAILURE;
  }
  if (test_encode_cyclic_upper_case_positive_k () != 0)
  {
    return EXIT_FAILURE;
  }
  if (test_decode_non_cyclic_lower_case_positive_k () != 0)
  {
    return EXIT_FAILURE;
  }
  if (test_decode_cyclic_lower_case_special_char_positive_k () != 0)
  {
    return EXIT_FAILURE;
  }

  if (test_decode_non_cyclic_lower_case_special_char_negative_k () != 0)
  {
    return EXIT_FAILURE;
  }
  if (test_decode_cyclic_lower_case_negative_k () != 0)
  {
    return EXIT_FAILURE;
  }

  if (test_decode_cyclic_upper_case_positive_k () != 0)
  {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
