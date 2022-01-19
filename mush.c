// Samson DeVol, CS344; Project3: Write a Shell in C, 1/20/22

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
  char input[2048], *new_argv[128];
  
  while(1)
  {
    char *token;
    int i = 0;

    // print command prompt
    printf("samshell%% ");
    fflush(stdout);

    // take input
    fgets(input, sizeof input, stdin);
    
    // parse input by whitespace, add to new_argv array
    if ((token = strtok(input, " \t\n\r")) != NULL){
      do {
        new_argv[i++] = token;
      } while ((token = strtok(NULL, " \t\n\r")) != NULL);
    }

    // terminate the array
    new_argv[i] = NULL;

    pid_t pid = fork();

    if (pid == 0){
      execvp(new_argv[0], new_argv);
      perror("exec");
      exit(1);
    }
    else {
      wait(NULL);
    }
    

  
  }
}