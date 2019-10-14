#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_SIZE 1024
FILE *f;

//A function to read input
void readCMD(char input[])
{
    fgets(input, MAX_SIZE , stdin);
  int c;

  //fgets adds '\n' at the end of string so we need to remove it
  while (*input != '\n' &&  *input != '\0') {
            ++input;
        }
        if (*input) {
            *input = '\0';
        } else {         // remove any extra characters in input
            while ((c = getchar()) != '\n' && c != EOF)
                continue;
        }
}


// A function to handle SIGCHLD signal
void handler(int sig)
{
  f = fopen("logfile.log", "a+");
  pid_t pid;

  pid = wait(NULL);

  if (f == NULL) { printf("Log file can't be reached");}
  else{
    if(pid!=-1)
      fprintf(f,"Pid %d exited.\n", pid);
  }
  fclose(f);

}

//A function to find '&' in a string
int findAmpersand(char str[]){
//check if & exists in the input line
  if( strchr(str, '&'))
  { //if it contains ampersand we need to remove it
    int j, n = strlen(str);
   for (int i=j=0; i<n; i++)
      if (str[i] != '&')
         str[j++] = str[i];

   str[j] = '\0';

   return 1;
  }
  else return 0;
}

//A function to split the input into an array of strings
void splitParameters(char *input,char *params[])
{
  //split it on the space char
  char splitter[]=" ";
  char *token=strtok(input,splitter);

  int index=0;
  while (token != NULL)
  {
      params[index]=token;
      token = strtok(NULL, " ");
      index++;
  }

  // Fill the rest of the array with null values
  for(;index<10;index++){
    params[index]=NULL;
  }
}

//A function to change directory
 void changeDirectory(char* params[]){
    char  *gdir;
    char  *dir;
    char  *to;
    char buf[MAX_SIZE];
    //gdir is the current directory
   gdir = getcwd(buf, sizeof(buf));
   dir = strcat(gdir, "/");
   to = strcat(dir, params[1]);

   chdir(to);

   if (chdir(to) == -1) {
           perror("error occured");}
           else{
             printf("your are now at %s\n", getcwd(buf, sizeof(buf)));
           }
 }

//A function to execute commands by forking a new child
 void executeCMD(char input[],char* params[],int ampersand){

//handle SIGCHLD signal in the case of &
   if(ampersand)
    signal(SIGCHLD, handler);

  // Forking a child
   pid_t pid = fork();
   int status;

   if(pid<0)
    printf("\n Operation Failed");
  else if(pid==0){
    execvp(params[0], params);
    exit(0);
  }
  else{
    if(!ampersand){
    waitpid(pid,&status,0);
    f = fopen("logfile.log", "a+");
    fprintf(f,"Pid %d exited.\n", pid);
    fclose(f);
    }
  }
}

int main(int argc, char const *argv[]) {
   f = fopen("logfile.log", "w");

  char input[MAX_SIZE];
  char *params[10];

  while(1){
    printf("SHELL > ");
    //1- Read input from user
    readCMD(input);

    //2- if input is exit , we need to exit program
    if(!strcmp("exit",input)){
      exit(0);
    }

    //3- check if input contains'&'
    int ampersand = findAmpersand(input);

    //4- Split input into an array of paramaters
    splitParameters(input,params);

    //5- Check if input is cd to change directory
    if (!strcmp(params[0], "cd")){
          changeDirectory(params);
          continue;
        }

    executeCMD(input,params,ampersand);
  }
  fclose(f);
  return 0;
}
