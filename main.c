#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

#define BUF_LEN 100

int main() {

  char prompt[BUF_LEN];
  char input[BUF_LEN];

  strcpy(prompt, "msh > ");

  while (true) {

    printf("%s", prompt);
    fgets(prompt, BUF_LEN, stdin);
    strtok(prompt, "\n");
    
  }

  return(0);

}
