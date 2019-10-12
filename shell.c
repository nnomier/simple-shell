#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

define MAX_SIZE 1024;


void readCMD(char *input)
{
  fgets(input, MAX_SIZE , stdin);

  int i;
 for(i=0;i<strlen(line);i++)
 {
   if(input[i]=='\n')
   {
     input[i]='\0';
     break;
   }
 }
}

public int findAmpersand(char str[]){
//check if & exists in the input line
  if( strchr(str, '&') return 1;
  else return 0;
}

void splitParameters(char *input,char *params[])
{
  char splitter[]=" ";
  char *token=strtok(input,splitter);

  int index=0;
  while (token != NULL)
  {
      params[index]=token;
      token = strtok(NULL, " ");
      index++;
  }
}

public void executeCMD(char* params[]){
  // Forking a child
   pid_t pid = fork();

   if(pid<0)
    printf("\n Operation Failed");
  else if(pid==0){
    printf("\n");
    execvp(params[0], params);
  }

}

int main(int argc, char const *argv[]) {
  char *input;
  char *params[10];

  //step 1: command shell should take the user command and its parameter(s)
   readCMD(input);
   splitParameters();

  return 0;
}
