#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "logic.h"
#include "header.h"

#define length 400
#define width 200

int data[length][width]; // contains color [0, length]
int coord[length]; // contains color [0, length]

extern int save_var(int first, int wid, int len);

void init_triangle ()
{
  for (int i = 0; i < length; ++i)
    for (int j = 0; j < width; ++j)
      data[i][j] = 0;

  for (int i = 0; i < width; ++i)
  {
    data[i][i] = length;
    coord[i] = i;
  }
  for (int i = width; i < length; ++i)
  {
    data[i][length - i] = length;
    coord[i] = length - i;
  }
  for (int i = 0; i < length; ++i)
    for (int j = 0; j < width; ++j)
      put_pixel (i , j , data[i][j]);
}

void calculate ()
{
  static int first = 0;
  first++;
  if (first == length)
    first = 0;
  int save = save_var(first, width, length);
  data[0][save] = length;
  data[0][coord[0]] = 0;
  data[0][coord[length-1]] = 0;
  
  for (int i = 0; i < length - 1; ++i)
  {
    data[i][coord[i + 1]] = 0;
    data[i][coord[i - 1]] = 0;
    data[i][coord[i + 2]] = 0;
    data[i][coord[i]] = rand() % 3 + 1;
    int tmp = coord[i];
    coord[i] = save;
    save = tmp;
  }
  coord[length - 1] = save;

  for (int i = 0; i < length; ++i)
    for (int j = 0; j < width; ++j)
      put_pixel (i , j , data[i][j]);
}