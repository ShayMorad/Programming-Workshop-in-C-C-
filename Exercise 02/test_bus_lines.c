#include "test_bus_lines.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define EQUAL 0

int is_sorted_by_duration (BusLine *start, BusLine *end)
{
  int bus_lines_length = end - start;
  for (int i = 0; i < bus_lines_length - 1; i++)
  {
    if (start[i].duration > start[i + 1].duration)
    {
      return 0;
    }
  }
  return 1;
}

int is_sorted_by_distance (BusLine *start, BusLine *end)
{
  int bus_lines_length = end - start;
  for (int i = 0; i < bus_lines_length - 1; i++)
  {
    if (start[i].distance > start[i + 1].distance)
    {
      return 0;
    }
  }
  return 1;
}

int is_sorted_by_name (BusLine *start, BusLine *end)
{
  int bus_lines_length = end - start;
  for (int i = 0; i < bus_lines_length - 1; i++)
  {
    if (strcmp(start[i].name, start[i + 1].name) > EQUAL)
    {
      return 0;
    }
  }
  return 1;
}

int check_element_in_sorted(int sorted_length,BusLine *start_sorted, BusLine
element_to_check )
{
  for (int i = 0; sorted_length > i; i++)
  {
    if (strcmp(start_sorted[i].name,element_to_check.name) == EQUAL)
    {
      return 1;
    }
  }
  return 0;
}

int is_equal (BusLine *start_sorted,
              BusLine *end_sorted, BusLine *start_original,
              BusLine *end_original)
{
  int original_length = end_original - start_original;
  int sorted_length = end_sorted - start_sorted;

  if (original_length != sorted_length)
  {
    return 0;
  }

  for (int i = 0; i < original_length; i++)
  {
    if ( (check_element_in_sorted (sorted_length, start_sorted,
                                 start_original[i])) == EQUAL)
    {
      return 0;
    }
  }
  return 1;
}


