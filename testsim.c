//Paul Passiglia
//cs 4760
//testsim.c is a simple program that proc_fan utilizes which 
//echoes out the command line arguments


#include <stdio.h>

int main(int argc, char *argv[])
{
  int counter;
  for (counter=0; counter < argc; counter++)
  {
    printf("argv[%2d]: %s\n", counter, argv[counter]);
  }
  return 0;
}
