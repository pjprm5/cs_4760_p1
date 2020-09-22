//Paul Passiglia
//cs 4760
//proc_fan.c 


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>
#include <getopt.h>
#include <errno.h>

int main(int argc, char *argv[])
{
  if (argc < 3)
  {
    fprintf (stderr, "Error: Missing arguments. Usage: ./proc_fan -n #\n");
    return (-1);
  }

  int pr_limit;      // Proc_fan.c will run up to the pr_limit of processes (initialized from command line).
  int pr_count = 0;  // Holds the number of ative children.

  int option; // Holds -n option.
  int cvalue; // Holds value of argument for -n option.
  int errnum; // Holds value of errno for perror usage.
  
  char str1[7]; // Holds arg0 like "testsim".
  char num1[2]; // Holds arg1 like "4".
  char num2[2]; // Holds arg2 like "10".
  
  int birthNum = 0;    // Holds total number of birthed child processes ever created in program execution. 
  pid_t childpid = 0;

  int sleepValue = 0;  // Holds int for arg1 for sleep() factor.
  int repeatValue = 0; // Holds int for arg2 for repeat factor.
  
  
  // Loop using getopt to parse command line options.
  while ((option = getopt (argc, argv, "n:")) != -1)
  {
    switch (option)
    {
      case 'n' :
        cvalue = atoi(optarg);
        if (cvalue > 20 || cvalue < 1)
        {
          fprintf(stderr, "Error: -n option must be from numbers 1-20. \n");
        }
        else
        {
          break;
        }
     case '?' :
        if (optopt == 'n')
        {
          fprintf(stderr, "Option -%c requires an argument. \n", optopt);
        }
        if (isprint (optopt))
        {
          fprintf(stderr, "Uknown Option '-%c'. \n", optopt);
        }
       
        return -1;
     default:
        printf("Default error.");
        return -1;
    }
  }
  
  printf("Excellent, you chose a max of %d processes to run simultaneously.\n\n", cvalue);

  pr_limit = cvalue; // Store cvalue into pr_limit because it holds process limit.
  
  // Open file stream to gain acces to testing.txt.
  FILE *fptr;
  if ((fptr = fopen("testing.txt", "r")) == NULL)
  {
    printf("Error! Opening file.\n");
    return -1;
  }
  
  // Main loop that depends upon returning three arguments at a time from testing.txt until EOF.
  while (fscanf(fptr, "%s %s %s", str1, &num1, &num2) == 3)
  {
    if (pr_count >= pr_limit)
    {
      // If pr_count == pr_limit wait for a child to finish using (wait) and decrement pr_count.
      printf("|ALERT| The pr_count is equal to pr_limit, waiting for a child to finish... |ALERT|\n\n");
      wait(0);
      pr_count--;
      printf("!!------> After waiting for child... <------!! #ACTIVE CHILDREN = %d.\n\n", pr_count);
    }
    
    // Child process breaks free below.
    if ((childpid = fork()) <= 0)
    {
      break;
    }
   
    pr_count++; // Keeps track of current number child processes. 
    birthNum++; // Keeps track of total birthed child processes.

    printf("!!!------> A CHILD IS BORN: childpid:%ld <------!!! #ACTIVE CHILDREN = %d.\n", (long)childpid, pr_count);
    fprintf(stderr, "    (The #%d child to be born. PID:%ld PPID:%ld CHILDPID:%ld.)\n\n", birthNum, (long)getpid(), (long)getppid(), (long)childpid);
    
    // Check to see if any children have been terminated without waiting and decrement pr_count.
    if (waitpid(-1, NULL, WNOHANG) > 0)
    {
      pr_count--;
      printf("!!!------> A CHILD IS SLAIN: childpid:%ld <------!!! #ACTIVE CHILDREN = %d.\n", (long)childpid, pr_count); 
    }
  }

  // Child that broke free has attributes displayed below and then is taken over by the execl().
  fclose(fptr);
  //fprintf(stderr, "i:%d process ID:%ld parent ID:%ld child ID:%ld\n", i, (long)getpid(), (long)getppid(), (long)childpid);
  execl(str1, str1, num1, num2, NULL);
  fprintf(stderr, "Execl error.");
  // Above printf should not print if execl() works correctly.

  return 0;
}
