#include "sort_bus_lines.h"

//sort bus lines

void swap (BusLine *p, BusLine *q);
void quick_sort_helper (BusLine *start, BusLine *end);

void swap (BusLine *p, BusLine *q)
{
  BusLine temp = *p;
  *p = *q;
  *q = temp;
}

void bubble_sort (BusLine *start, BusLine *end)
{
  int n = (int) (end - start);
  for (int i = 0; i < n - 1; ++i)
    {
      for (int j = 0; j < n - i - 1; ++j)
        {
          if ((start + j)->distance > (start + j + 1)->distance)
            {
              swap (start + j, start + j + 1);
            }
        }
    }
}

BusLine *partition (BusLine *start, BusLine *end)
{
  int n = (int) (end - start);
//  BusLine *pivot = (end - 1);
  BusLine *pivot = end;
  BusLine *i = start - 1;
  for (int j = 0; j < n; ++j)
    {
      if ((start + j)->duration <= pivot->duration)
        {
          i++;
          swap (i, start + j);
        }
    }
  swap ((i + 1), end);
  return i + 1;
}

void quick_sort_helper (BusLine *start, BusLine *end)
{
  if (start < end)
    {
      BusLine *p = partition (start, end);
      quick_sort_helper (start, p - 1);
      quick_sort_helper (p + 1, end);
    }
}

void quick_sort (BusLine *start, BusLine *end)
{
  quick_sort_helper (start, end - 1);
}