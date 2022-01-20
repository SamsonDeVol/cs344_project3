// Samson DeVol, CS344; Project3: Write a Shell in C, 1/20/22

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
  char input[2048], *new_argv[128];

  while(1)
  {
    int i = 0;
    long size = pathconf(".", _PC_PATH_MAX);
    char *token, *buf, *ptr = NULL;
    
    // find cwd (Source: https://pubs.opengroup.org/onlinepubs/007904975/functions/getcwd.html)
    if ((buf = (char *)malloc((size_t)size)) != NULL)
      ptr = getcwd(buf, (size_t)size);

    // print command prompt
    printf("%s %% ", ptr);
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

    // check if first command is cd
    if (!strcmp(new_argv[0], "cd")){
      if (chdir(new_argv[1]) != 0)
        perror("dir");
    }
    // check ig first command is exit
    else if (!strcmp(new_argv[0], "exit")){
      exit(0);
    }
    // else fork and exec process given theres no error
    else {
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
}