#include <stdio.h>
#include <unistd.h>
#include "header.h"
#include "logic.h"

int main ()
{
  init_window ();
  init_triangle ();
  int check = 0;
  while (!check)
  {
    calculate ();
    check = flush ();
  }
}