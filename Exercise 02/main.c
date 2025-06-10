#include "sort_bus_lines.h"
#include "test_bus_lines.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_NUMBER_OF_LINES 2147483647
#define MAX_INPUT_LINE 60
#define MAX_BUS_ARG 20
#define MIN_NUMBER_OF_LINES 1
#define MIN_DURATION 10
#define MAX_DURATION 100
#define MIN_DISTANCE 0
#define MAX_DISTANCE 1000
#define NULL_CHAR '\0'

/**
 * Runs the sort_lines program.
 * Can sort by bus lines name, duration and distance.
 * (1) Insert 'test' argument to run the program's tests.
 * (2) Insert 'by_duration' or 'by_distance' to sort by duration or distance of
 * the lines using the quick sort algorithm.
 * (3) Insert 'by_name' to sort by name using the bubble sort algorithm.
 */
int make_copy (BusLine *start, BusLine *end, BusLine **copy_start);
int run_test (BusLine *start, BusLine *end);
void test_1 (BusLine *start, BusLine *end);
void test_2 (BusLine *start, BusLine *end);
void test_3 (BusLine *start, BusLine *end);
int arg_checks (int argc, char *argv[]);
int get_number_of_lines ();
int get_busses (BusLine *start, int number_of_lines);
void input_bus (BusLine *ptr);
int check_bus_info (BusLine *ptr, char bus_name[], int bus_distance, int
bus_duration);
void run_command (BusLine *start_pointer, BusLine *end_pointer, char *argv[]);

int main (int argc, char *argv[])
{
  if (arg_checks (argc, argv) == false)
  {
    return EXIT_FAILURE;
  }
  int number_of_lines = get_number_of_lines ();
  BusLine start;
  BusLine *start_pointer = &start;
  start_pointer = malloc (number_of_lines * sizeof (BusLine));
  if (start_pointer == NULL)
  {
    printf ("ERROR: COULD NOT ALLOCATE MEMORY, MAIN FUNC FAILED.");
    free (start_pointer);
    return EXIT_FAILURE;
  }
  BusLine *end_pointer = start_pointer + number_of_lines;
  get_busses (start_pointer, number_of_lines);
  run_command (start_pointer, end_pointer, argv);
  free (start_pointer);
  return EXIT_SUCCESS;
}

void run_command (BusLine *start_pointer, BusLine *end_pointer, char *argv[])
{
  if (strcmp (argv[1], "by_name") == 0)
  {
    bubble_sort (start_pointer, end_pointer);
    for (int i = 0; i < amount_of_lines (start_pointer, end_pointer); i++)
    {
      printf ("%s,%d,%d\n", (*(start_pointer + i)).name, (*(start_pointer + i))
          .distance, (*(start_pointer + i)).duration);
    }
  }
  else if (strcmp (argv[1], "by_duration") == 0)
  {
    quick_sort (start_pointer, end_pointer, DURATION);
    for (int i = 0; i < amount_of_lines (start_pointer, end_pointer); i++)
    {
      printf ("%s,%d,%d\n", (*(start_pointer + i)).name, (*(start_pointer + i))
          .distance, (*(start_pointer + i)).duration);
    }
  }
  else if (strcmp (argv[1], "by_distance") == 0)
  {
    quick_sort (start_pointer, end_pointer, DISTANCE);
    for (int i = 0; i < amount_of_lines (start_pointer, end_pointer); i++)
    {
      printf ("%s,%d,%d\n", (*(start_pointer + i)).name, (*(start_pointer + i))
          .distance, (*(start_pointer + i)).duration);
    }
  }
  else if (strcmp (argv[1], "test") == 0)
  {
    run_test (start_pointer, end_pointer);
  }
}

/** Checks if args amount and inputs are correct. */
int arg_checks (int argc, char *argv[])
{
  if (argc != 2 || ((strcmp (argv[1], "test") != 0) && (strcmp (argv[1],
                                                                "by_distance")
                                                        != 0)
                    && (strcmp (argv[1], "by_duration") != 0) &&
                    (strcmp (argv[1], "by_name") != 0)))
  {
    fprintf (stdout, "USAGE: WRONG ARGUMENT COUNT, INSERT ONLY 1");
    return 0;
  }
  return 1;
}

/** Creates a copy of the original BusLine struct. */
int make_copy (BusLine *start, BusLine *end, BusLine **copy_start)
{
  int lines_length = amount_of_lines (start, end);
  *copy_start = malloc (lines_length * sizeof (BusLine));
  if (*copy_start == NULL)
  {
    return 0;
  }
  memcpy (*copy_start, start, lines_length * sizeof (BusLine));
  return 1;
}

/** Runs test mode. */
int run_test (BusLine *start, BusLine *end)
{
  BusLine *copy_start = NULL, *copy_end = NULL;
  int make_copy_res = make_copy (start, end, &copy_start);
  int lines_length = amount_of_lines (start, end);
  copy_end = copy_start + lines_length;
  if (make_copy_res == false)
  {
    free (copy_start);
    fprintf (stdout, "TEST MODE FAILED: COULD NOT CREATE COPY\n");
    return EXIT_FAILURE;
  }
  test_1 (copy_start, copy_end);
  if (is_equal (copy_start, copy_end, start, end) == true)
  {
    fprintf (stdout, "TEST 2 PASSED: COPY AND ORIGINAL ARE EQUAL\n");
  }
  else
  {
    fprintf (stdout, "TEST 2 FAILED: COPY AND ORIGINAL ARE NOT EQUAL\n");
  }
  test_2 (copy_start, copy_end);
  if (is_equal (copy_start, copy_end, start, end) == true)
  {
    fprintf (stdout, "TEST 4 PASSED: COPY AND ORIGINAL ARE EQUAL\n");
  }
  else
  {
    fprintf (stdout, "TEST 4 FAILED: COPY AND ORIGINAL ARE NOT EQUAL\n");
  }
  test_3 (copy_start, copy_end);
  if (is_equal (copy_start, copy_end, start, end) == true)
  {
    fprintf (stdout, "TEST 6 PASSED: COPY AND ORIGINAL ARE EQUAL\n");
  }
  else
  {
    fprintf (stdout, "TEST 6 FAILED: COPY AND ORIGINAL ARE NOT EQUAL\n");
  }
  free (copy_start);
  return EXIT_SUCCESS;
}

void test_1 (BusLine *start, BusLine *end)
{
  quick_sort (start, end, DISTANCE);
  int test_res = is_sorted_by_distance (start, end);
  if (test_res == false)
  {
    fprintf (stdout, "TEST 1 FAILED: NOT SORTED BY DISTANCE\n");
    return;
  }
  fprintf (stdout, "TEST 1 PASSED: SORTED BY DISTANCE\n");
}

void test_2 (BusLine *start, BusLine *end)
{
  quick_sort (start, end, DURATION);
  int test_res = is_sorted_by_duration (start, end);
  if (test_res == false)
  {
    fprintf (stdout, "TEST 3 FAILED: NOT SORTED BY DURATION\n");
    return;
  }
  fprintf (stdout, "TEST 3 PASSED: SORTED BY DURATION\n");
}

void test_3 (BusLine *start, BusLine *end)
{
  bubble_sort (start, end);
  int test_res = is_sorted_by_name (start, end);
  if (test_res == false)
  {
    fprintf (stdout, "TEST 5 FAILED: NOT SORTED BY NAME\n");
    return;
  }
  fprintf (stdout, "TEST 5 PASSED: SORTED BY NAME\n");
}

/** Getting wanted number of lines from user. */
int get_number_of_lines ()
{
  int number_of_lines = 0;
  int *number = &number_of_lines;
  while (*number <= 0 || *number > MAX_NUMBER_OF_LINES)
  {
    printf ("Enter number of lines. Then enter\n");
    char input[MAX_INPUT_LINE];
    fgets (input, MAX_INPUT_LINE, stdin);
    if (sscanf (input, "%d", number) != 1
        || sscanf (input, "%d", number) == EOF ||
        *number < MIN_NUMBER_OF_LINES || *number > MAX_NUMBER_OF_LINES)
    {
      printf ("ERROR: You did not enter a positive integer.\n");
    }
  }
  return number_of_lines;
}

/** Inserting each bus line into the struct. */
int get_busses (BusLine *start, int number_of_lines)
{
  for (int i = 0; number_of_lines > i; i++)
  {
    input_bus (start + i);
  }
  return EXIT_SUCCESS;
}

/** Getting bus line info. */
void input_bus (BusLine *ptr)
{
  char bus_name[MAX_BUS_ARG];
  int bus_distance = 0, bus_duration = 0;
  int error = 1;
  while (error != 0)
  {
    printf ("Enter line info. Then enter\n");
    char input[MAX_INPUT_LINE];
    if (fgets (input, MAX_INPUT_LINE, stdin) == NULL)
    {
      printf ("ERROR: COULD NOT RETRIEVE LINE INFO. ENTER IN FORMAT <string>,"
              "<int>,<int>\n");
      continue;
    }
    int res = sscanf (input, "%[^,],%d,%d", bus_name, &bus_distance,
                      &bus_duration);
    if (res == EOF || res != 3)
    {
      printf ("ERROR: COULD NOT RETRIEVE LINE INFO. ENTER IN FORMAT <string>,"
              "<int>,<int>\n");
      continue;
    }
    error = check_bus_info (ptr, bus_name, bus_distance, bus_duration);
  }
}

/** Checks if the bus line info is correct. */
int check_bus_info (BusLine *ptr, char bus_name[], int bus_distance, int
bus_duration)
{
  int i = 0;
  while (bus_name[i] != NULL_CHAR)
  {
    if ((bus_name[i] >= 'a' && bus_name[i] <= 'z') || (bus_name[i] >= '0' &&
                                                       bus_name[i] <= '9'))
    {
      i++;
    }
    else
    {
      printf ("ERROR: WRONG BUS NAME\n");
      return EXIT_FAILURE;
    }
  }
  if (bus_distance >= MIN_DISTANCE && bus_distance <= MAX_DISTANCE)
  {
    if (bus_duration >= MIN_DURATION && bus_duration <= MAX_DURATION)
    {
      ptr->distance = bus_distance;
      ptr->duration = bus_duration;
      strcpy (ptr->name, bus_name);
      return EXIT_SUCCESS;
    }
    else
    {
      printf ("ERROR: WRONG DURATION\n");
      return EXIT_FAILURE;
    }
  }
  else
  {
    printf ("ERROR: WRONG DISTANCE\n");
    return EXIT_FAILURE;
  }
}
