#ifndef EX2_REPO_SORTBUSLINES_H
#define EX2_REPO_SORTBUSLINES_H

/**
 * TODO add documentation
 */
typedef struct BusLine
{
    int line_number, distance, duration;
} BusLine;

/**
 * TODO add documentation
 */
void bubble_sort (BusLine *start, BusLine *end);

/**
 * TODO add documentation
 */
void quick_sort (BusLine *start, BusLine *end);

/**
 * TODO add documentation
 */
BusLine *partition (BusLine *start, BusLine *end);

#endif //EX2_REPO_SORTBUSLINES_H
