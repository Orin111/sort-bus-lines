#include "sort_bus_lines.h"
#include "test_bus_lines.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define INVALID 0
#define VALID 1
#define MAX 60
#define BASE 10
#define MAX_LINE 999
#define MAX_DIS 1000
#define MAX_DUR 100
#define USAGE_ELEMENTS "USAGE: incorrect number of arguments\n"
#define USAGE_COMMAND "USAGE: unknown command\n"
#define NUM_OF_LINES "ERROR: number of lines should be an integer bigger than \
0\n"
#define LINE_NUM "ERROR: line number should be an integer between 1 and 999 \
(includes)\n"
#define DISTANCE "ERROR: distance should be an integer between 0 and 1000 \
(includes)\n"
#define DURATION "Error: duration should be an integer between 10 and 100 \
(includes) \n"
#define TEST_1_P "TEST 1 PASSED: array is sorting by distance \n"
#define TEST_2_P "TEST 2 PASSED: array is equal \n"
#define TEST_3_P "TEST 3 PASSED: array is sorted by duration \n"
#define TEST_4_P "TEST 4 PASSED: array is equal \n"
#define TEST_1_F "TEST 1 FAILED:  array is not sorting by distance\n"
#define TEST_2_F "TEST 2 FAILED: array is not equal \n"
#define TEST_3_F "TEST 3 FAILED: array is not sorted by duration \n"
#define TEST_4_F "TEST 4 FAILED: array is not equal \n"
#define ENTER_NUM_LINES "Enter number of lines. Then enter\n"
#define BUBBLE "bubble"
#define QUICK "quick"
#define TEST "test"
#define B 'b'
#define T 't'
#define Q 'q'
#define LINE_INFO "Enter line info. Then enter\n"


/**
 * This is the main file
 */

//declarations
/**
 *
 * @param all_lines
 * @param number_of_lines
 */
void print_arr (BusLine *all_lines, long number_of_lines);

/**
 *
 * @param argc number of parameters user entered
 * @param argv parameters from the user
 * @param all_lines an array of all lines
 * @param number_of_lines int the user entered
 * @return 0 if the command invalid or malloc didn't work, 1 else
 */
int get_lines (BusLine *all_lines, const long *number_of_lines);

/**
 *
 * @param argc number of parameters user entered
 * @param argv parameters from the user
 * @return 1 if the command (argv[1]) is one of these: bubble/ quick/ test
 * and the argc = 2, else return - o
 */
int check_command_validation (int argc, char *argv[]);

/**
 *
 * @return ask the user for number of lines and return the number he entered
 * if the number the user entered isn`t valid- return 0.
 */
long get_number_of_lines ();

/**
 *
 * @param number_of_lines an int
 * @return 1 if the number of lines is a long positive number != 0, else 0
 */
int check_number_of_lines_validation (long number_of_lines);

/**
 *
 * @param argv parameters from the user
 * @return b> bubble; q> quick; t> test; 0>else
 */
char check_command (char *argv[]);

/**
 *
 * @param all_lines  an array of all lines
 * @param number_of_lines an int
 * the function run all test
 */
int test_mode (BusLine *all_lines, long number_of_lines);

/**
 * 
 * @param all_lines_cpy a pointer to the target location
 * @param all_lines a pointer to the source location
 * @param number_of_lines an int
 * the function copy the source location to the target location using memcpy
 */
void cpy (BusLine *dest, const BusLine *src, long number_of_lines);

/**
 * 
 * @param all_lines  an array of all lines
 * @param all_lines_by_dis  an array of all lines sorted by distance
 * @param all_lines_by_dur an array of all lines sorted by duration
 * @param number_of_lines an int
 * the function run all test and print passed/ failed per each
 */
void run_test
    (BusLine *all_lines, BusLine *all_lines_by_dis, BusLine *all_lines_by_dur,
     long number_of_lines);

/**
 * 
 * @param all_lines  an array of all lines
 * @param number_of_lines an int
 * the function add number_of_lines lines the user enter to the array
 */
void add_line_to_lines (BusLine *all_lines, long number_of_lines);

/**
 * 
 * @param new_line a BusLine pointer
 * @return the func ask the user for a line info and return 1 if the line info
 * is valid 0 else
 */
int get_line_info (BusLine *new_line);

/**
 * 
 * @param line_num 
 * @param distance 
 * @param duration 
 * @return 1 if all valid, 0 else
 */
int check_line_info_validation (int line_num, int distance, int duration);

/**
 *
 * @param line_number an int the user entered
 * @return 1 if 1>=line_number>=999, 0 else
 */
int check_line_number_validation (int line_number);

/**
 *
 * @param distance an int the user entered
 * @return 1 if 0>=distance>=1000, 0 else
 */
int check_distance_validation (int distance);

/**
 *
 * @param duration an int the user entered
 * @return 1 if 10>=distance>=100, 0 else
 */
int check_duration_validation (int duration);

int main (int argc, char *argv[])
{
  if (!check_command_validation (argc, argv))
    {
      return EXIT_FAILURE;
    }
  long number_of_lines = get_number_of_lines ();
  BusLine *all_lines = (BusLine *) malloc (
      number_of_lines * sizeof (BusLine));
  if (!get_lines (all_lines, &number_of_lines))
    {
      free(all_lines);
      return EXIT_FAILURE;
    }
  if (check_command (argv) == B)
    {
      bubble_sort (all_lines, &(all_lines[number_of_lines]));
      print_arr (all_lines, number_of_lines);
      free (all_lines);
      return EXIT_SUCCESS;
    }
  else if (check_command (argv) == Q)
    {
      quick_sort (all_lines, &(all_lines[number_of_lines]));
      print_arr (all_lines, number_of_lines);
      return EXIT_SUCCESS;
    }
  else if (check_command (argv) == T)
    {
      if (!test_mode (all_lines, number_of_lines))
        {
          free(all_lines);
          return EXIT_FAILURE;
        }
    }
  free (all_lines);
  EXIT_SUCCESS;
}


//functions

void print_arr (BusLine *all_lines, long number_of_lines)
{
  for (int i = 0; i < number_of_lines; ++i)
    {
      printf ("%d,%d,%d\n", all_lines[i].line_number,
              all_lines[i].distance, all_lines[i].duration);
    }
}

int get_lines (BusLine *all_lines, const long *number_of_lines)
{
  if (!all_lines)
    {
      return INVALID;
    }
  add_line_to_lines (all_lines, *number_of_lines);
  return VALID;
}

int check_command_validation (int argc, char *argv[])
{
  if (argc != 2)
    {
      fprintf (stdout, USAGE_ELEMENTS);
      return INVALID;
    }

  char command[BASE];
  memcpy (command, argv[1], BASE);
  if (strcmp (command, BUBBLE) != 0)
    {
      if (strcmp (command, QUICK) != 0)
        {
          if (strcmp (command, TEST) != 0)
            {
              fprintf (stdout, USAGE_COMMAND);
              return INVALID;
            }
        }
    }
  return VALID;
}

long get_number_of_lines ()
{
  fprintf (stdout, ENTER_NUM_LINES);
  char number_of_lines_str[MAX];
  fgets (number_of_lines_str, MAX, stdin);
  long number_of_lines = strtol (number_of_lines_str,
                                 NULL, BASE);
  if (check_number_of_lines_validation (number_of_lines))
    {
      return number_of_lines;
    }
  return get_number_of_lines ();
}

int check_number_of_lines_validation (long number_of_lines)
{
  if (number_of_lines <= 0)
    {
      fprintf (stdout, NUM_OF_LINES);
      return INVALID;
    }
  return VALID;
}

char check_command (char *argv[])
{
  char command[BASE];
  memcpy (command, argv[1], BASE);
  if (strcmp (command, "bubble") == 0)
    {
      return 'b';
    }
  if (strcmp (command, "quick") == 0)
    {
      return 'q';
    }
  if (strcmp (command, "test") == 0)
    {
      return 't';
    }
  return '0';
}

int test_mode (BusLine *all_lines, long number_of_lines)
{
  //copy
  BusLine *all_lines_by_dis = malloc (number_of_lines * sizeof (BusLine));
  if (all_lines_by_dis == NULL)
    {
      return INVALID;
    }
  BusLine *all_lines_by_dur = malloc (number_of_lines * sizeof (BusLine));
  if (all_lines_by_dur == NULL)
    {
      free (all_lines_by_dur);
      return INVALID;
    }
  cpy (all_lines_by_dis, all_lines, number_of_lines);
  cpy (all_lines_by_dur, all_lines, number_of_lines);

  //sorted
  bubble_sort (all_lines_by_dis,
               &(all_lines_by_dis[number_of_lines]));
  quick_sort (all_lines_by_dur,
              &(all_lines_by_dur[number_of_lines]));
  run_test (all_lines, all_lines_by_dis,
            all_lines_by_dur, number_of_lines);
  free (all_lines_by_dis);
  free (all_lines_by_dur);
  return VALID;
}

void cpy (BusLine *dest, const BusLine *src, long number_of_lines)
{
  if (!dest)
    {
      return;
    }
  memcpy (dest, src,
          number_of_lines * sizeof (*src));
}

void run_test
    (BusLine *all_lines, BusLine *all_lines_by_dis, BusLine *all_lines_by_dur,
     long number_of_lines)
{
  //test1
  if (is_sorted_by_distance
      (all_lines_by_dis, &all_lines_by_dis[number_of_lines]))
    {
      fprintf (stdout, TEST_1_P);
    }
  else
    {
      fprintf (stdout, TEST_1_F);
    }

  //test2
  if (is_equal (all_lines_by_dis,
                &all_lines_by_dis[number_of_lines],
                all_lines, &all_lines[number_of_lines]))
    {
      fprintf (stdout, TEST_2_P);
    }
  else
    {
      fprintf (stdout, TEST_2_F);
    }

  //test3
  if (is_sorted_by_duration (all_lines_by_dur,
                             &all_lines_by_dur[number_of_lines]))
    {
      fprintf (stdout, TEST_3_P);
    }
  else
    {
      fprintf (stdout, TEST_3_F);
    }

  //test4
  if (is_equal (all_lines_by_dur,
                &all_lines_by_dur[number_of_lines],
                all_lines, &all_lines[number_of_lines]))
    {
      fprintf (stdout, TEST_4_P);
    }
  else
    {
      fprintf (stdout, TEST_4_F);
    }
}

void add_line_to_lines (BusLine *all_lines, long number_of_lines)
{
  int i = 0;
  while (i < number_of_lines)
    {
      BusLine new_line;
      if (get_line_info (&new_line))
        {
          all_lines[i] = new_line;
          i++;
        }
    }
}

int get_line_info (BusLine *new_line)
{
  fprintf (stdout, LINE_INFO);
  int line_num, distance, duration;
  char buffer[MAX];
  fgets (buffer, MAX, stdin);
  sscanf (buffer, "%d,%d,%d", &line_num, &distance, &duration);
  if (check_line_info_validation (line_num, distance, duration))
    {
      new_line->line_number = line_num;
      new_line->distance = distance;
      new_line->duration = duration;
      return VALID;
    }
  return INVALID;
}

int check_line_info_validation (int line_num, int distance, int duration)
{
  if (check_line_number_validation (line_num) &&
      check_distance_validation (distance)
      && check_duration_validation (duration))
    {
      return VALID;
    }
  return INVALID;
}

int check_line_number_validation (int line_number)
{
  if (1 > line_number || line_number > MAX_LINE)
    {
      fprintf (stdout, LINE_NUM);
      return INVALID;
    }
  return VALID;
}

int check_distance_validation (int distance)
{
  if (0 > distance || distance > MAX_DIS)
    {
      fprintf (stdout, DISTANCE);
      return INVALID;
    }
  return VALID;
}

int check_duration_validation (int duration)
{
  if (BASE > duration || duration > MAX_DUR)
    {
      fprintf (stdout, DURATION);
      return INVALID;
    }
  return VALID;
}
