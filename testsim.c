//Paul Passiglia
//cs 4760
//testsim.c is a simple program that proc_fan utilizes which 
//echoes out the command line arguments


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  printf("Program testsim begins.\n");
  int counter;
  char *progName = argv[0];
  int sleepValue = atoi(argv[1]);
  int repeatValue = atoi(argv[2]);

  for (counter=0; counter < repeatValue; counter++)
  {
    printf("Program Name -> arg[0]:%s, Sleep Value -> arg[1]:%d, Repeat Value -> arg[2]:%d.\n", progName, sleepValue, repeatValue);
    sleep(sleepValue);
  }
  printf("\n");
  return 0;
}
