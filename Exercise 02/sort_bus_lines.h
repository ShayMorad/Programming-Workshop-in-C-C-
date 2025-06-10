#ifndef EX2_REPO_SORTBUSLINES_H
#define EX2_REPO_SORTBUSLINES_H
// write only between #define EX2_REPO_SORTBUSLINES_H and #endif
// EX2_REPO_SORTBUSLINES_H
#include <string.h>
#define NAME_LEN 21
/**
 * typdef of a BusLine Struct that has the line name, distance and duration.
 */
typedef struct BusLine
{
    char name[NAME_LEN];
    int distance, duration;
} BusLine;
typedef enum SortType
{
    DISTANCE,
    DURATION
} SortType;

/**
 * Bubble Sort algorithm using pointers.
 */
void bubble_sort (BusLine *start, BusLine *end);

/**
 * Quick Sort algorithm using pointers.
 */
void quick_sort (BusLine *start, BusLine *end, SortType sort_type);

/**
 * This function sorts the partition part in the quick sort algorithm.
 */
BusLine *partition (BusLine *start, BusLine *end, SortType sort_type);
int amount_of_lines (BusLine *start, BusLine *end);
// write only between #define EX2_REPO_SORTBUSLINES_H and #endif
// EX2_REPO_SORTBUSLINES_H
#endif //EX2_REPO_SORTBUSLINES_H
