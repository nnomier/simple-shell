#include <stdio.h>

int main(int argc, char const *argv[]) {
  FILE *f;
  int j=0;
  while(j<5){
f = fopen("x.log", "a+"); // a+ (create + append) option will allow appending which is useful in a log file
if (f == NULL) { /* Something is wrong   */}
fprintf(f, "Im logging somethig ..\n");
j++;}

  return 0;
}
