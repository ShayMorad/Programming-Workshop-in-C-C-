#ifndef EX2_REPO_TESTBUSLINES_H
#define EX2_REPO_TESTBUSLINES_H
// write only between #define EX2_REPO_TESTBUSLINES_H
// and #endif //EX2_REPO_TESTBUSLINES_H
#include "sort_bus_lines.h"

/**
 * Runs a test that checks if the bus lines are sorted by distance.
 * Returns 1 if the array is sorted correctly, 0 otherwise.
 */
int is_sorted_by_distance (BusLine *start, BusLine *end);

/**
 * Runs a test that checks if the bus lines are sorted by duration.
 * Returns 1 if the array is sorted correctly, 0 otherwise.
 */
int is_sorted_by_duration (BusLine *start, BusLine *end);

/**
 * Runs a test that checks if the bus lines are sorted by name.
 * Returns 1 if the array is sorted correctly, 0 otherwise.
 */
int is_sorted_by_name (BusLine *start, BusLine *end);

/**
 * Checks between an original array and its sorted version.
 * Returns 1 if both arrays have the same elements, 0 otherwise.
 */
int is_equal (BusLine *start_sorted,
              BusLine *end_sorted, BusLine *start_original,
              BusLine *end_original);
// write only between #define EX2_REPO_TESTBUSLINES_H
// and #endif //EX2_REPO_TESTBUSLINES_H
#endif //EX2_REPO_TESTBUSLINES_H
