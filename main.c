#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

#define BUF_LEN 255
#define tokDelim " -"

void scanInput(char *userInput, char **tokens) {

  char *scanString;
  int i = 0;

  strtok(userInput, "#"); //Check for comments first
  scanString = strtok(userInput, tokDelim);
  while (scanString != NULL){

    tokens[i] = scanString;
    scanString = strtok(NULL, tokDelim);
    i++;

  }

}

int main() {

  int ShowTokens = 0;
  char prompt[BUF_LEN];
  char input[BUF_LEN];
  char *tokens[BUF_LEN];

  strcpy(prompt, "msh > ");

  while (true) {

    printf("%s", prompt);
    fgets(input, BUF_LEN, stdin);
    input[strlen(input)-1] = '\0'; // Removes trailing \n from stdin
    scanInput(input, tokens);

    if (strcmp(tokens[0], "setPrompt") == 0)
      strcpy(prompt, tokens[1]);
    else if (strcmp(tokens[0], "done") == 0)
      exit(0);
    else printf("No Command %s found.\n", tokens[0]);

  }

  return(0);

}
