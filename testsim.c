//Paul Passiglia
//cs 4760
//testsim.c is a simple program that proc_fan utilizes which 
//echoes out the command line arguments


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  printf("A Program testsim begins...\n");
  int counter;
  char *progName = argv[0];
  int sleepValue = atoi(argv[1]);
  int repeatValue = atoi(argv[2]);

  for (counter=1; counter <= repeatValue; counter++)
  {
    printf("Iteration[%d] of Program: [%s %d %d].\n", counter, progName, sleepValue, repeatValue);
    sleep(sleepValue);
  }
  printf("\n!------> *The Program: [%s %d %d] has ended.* <------!\n\n", progName, sleepValue, repeatValue);
  return 0;
}
