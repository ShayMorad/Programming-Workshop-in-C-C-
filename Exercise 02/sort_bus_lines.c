#include "sort_bus_lines.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define EQUAL 0

void swap_lines (BusLine *x, BusLine *y)
{
  BusLine z = *x;
  *x = *y;
  *y = z;
}

int amount_of_lines (BusLine *start, BusLine *end)
{
  return (end - start);
}

void bubble_sort (BusLine *start, BusLine *end)
{
  int number_of_lines = amount_of_lines (start, end);
  for (int i = 0; i < number_of_lines; i++)
  {
    for (int j = 0; j < (number_of_lines - i - 1); j++)
    {
      BusLine *x = start + j;
      BusLine *y = start + j + 1;
      if (strcmp (x->name, y->name) > EQUAL)
      {
        swap_lines (x, y);
      }
    }
  }
}

void quick_sort (BusLine *start, BusLine *end, SortType sort_type)
{
  if (start < end)
  {
    BusLine *middle = partition (start, end, sort_type);
    quick_sort (start, middle, sort_type);
    quick_sort (middle + 1, end, sort_type);
  }
}

BusLine *partition (BusLine *start, BusLine *end, SortType sort_type)
{
  int lines = amount_of_lines (start, end);
  int l = -1;
  int pivot = lines - 1;
  for (int i = 0; i < lines - 1; i++)
  {
    if (sort_type == DISTANCE)
    {
      if ((*(start + i)).distance <= (*(start + pivot)).distance)
      {
        l++;
        swap_lines (start + l, start + i);
      }
    }
    else if (sort_type == DURATION)
    {
      if ((*(start + i)).duration <= (*(start + pivot)).duration)
      {
        l++;
        swap_lines (start + l, start + i);
      }
    }
  }
  swap_lines (start + l + 1, start + pivot);
  return start + l + 1;
}