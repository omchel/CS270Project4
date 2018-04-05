/*
  CS270Project4
  Systems Programming Project 4

  Authors: Kenton Carrier and Chelina Ortiz Montanez
*/

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include "functions.h"

#define BUF_LEN 255
#define tokDelim " -"

/* function scanInput:
  Retrieves the user input and separates in into tokens.
  Determines how to parse the commands given.
*/
int scanInput(char *userInput, char **tokens) {

  char* scanString;
  int i = 0;

  strtok(userInput, "#"); //Check for comments first
  scanString = strtok(userInput, tokDelim);
  //Uses the remaining string as the new prompt
  if (strcmp(scanString, "setprompt") == 0){ // if the command given was 'setpromt'

    while (scanString != NULL){

      tokens[i] = scanString;
      scanString = strtok(NULL, "\"");
      i++;

    }

  }
  else if (strcmp(scanString, "done") == 0){ // if the command given was 'done'

    while (scanString != NULL){

      tokens[i] = scanString;
      scanString = strtok(NULL, " ");
      i++;

    }

  }
  else if(strcmp(scanString, "setvar") == 0){ // if the command given was 'setvar'

    tokens[0] = scanString;
    tokens[1] = strtok(NULL, " ");
    tokens[2] = strtok(NULL, "\"");
    i = 3;

  }
  //Separates the rest of the tokens
  else {

    while (scanString != NULL){

      tokens[i] = scanString;
      scanString = strtok(NULL, tokDelim);
      i++;

    }

  }

  return i;

}
/* checkVars function:
  checks to see if the user inputs a vaiable to use, then
  finds it in the structure and if it is sucessful, it 
  returns the value stored in that variable.
*/
void checkVars(char** tokens, int numTokens, struct newVar* vars, int numVars) {

  for (int i = 0; i < numVars; i++){

    for (int j = 0; j < numTokens; j++){

      char varName[BUF_LEN];
      strcpy(varName, tokens[j]);
      strcpy(varName, strtok(varName, "^"));

      if (strcmp(varName, vars[i].name) == 0) // if we can match the user input with an existing variable
        tokens[j] = vars[i].valStr;

    }

  }

}
/* checkProcs function:
  cheks if any of the background processes is not finished.
*/
int checkProcs(int numProcs, struct proc* currentProcs) {

  int childIndex;
  pid_t finishedProc;

  finishedProc = waitpid(-1, 0, WNOHANG);
  if (finishedProc != 0) { // if there are processes running in the background

    for (int i = 0; i < numProcs; i++) {

      if (currentProcs[i].pID == finishedProc){

        printf("Process finished: %s\n", currentProcs[i].pName); // list the processes still running 
        for (int j = i; j < numProcs; j++) {
          currentProcs[j] = currentProcs[j+1];
        }
        numProcs--;

      }
    }

  }

  return numProcs;

}
// main
int main() {

  struct proc procs[BUF_LEN];
  int numTokens, numProcs = 0, numVars = 0;
  char prompt[BUF_LEN];
  char input[BUF_LEN];
  char *tokens[BUF_LEN];
  struct newVar vars[BUF_LEN];

  strcpy(prompt, "msh > ");

  while (true) {

    numProcs = checkProcs(numProcs, procs); // check proceses running on the background every time there is a new command

    printf("%s", prompt);
    fgets(input, BUF_LEN, stdin);
    input[strlen(input)-1] = '\0'; // Removes trailing \n from stdin. From exectest.c by Raphael Finkel
    numTokens = scanInput(input, tokens);
    checkVars(tokens, numTokens, vars, numVars);
    // check the user input and determine which function is being asked to do 
    if (strcmp(tokens[0], "setprompt") == 0)
      strcpy(prompt, tokens[1]);
    else if (strcmp(tokens[0], "done") == 0)
      exitShell(tokens, numTokens);
    else if (strcmp(tokens[0], "setvar") == 0)
      vars[numVars] = setvar(tokens, vars, &numVars);
    else if (strcmp(tokens[0], "run") == 0)
      run(tokens[1], tokens[2], numTokens);
    else if (strcmp(tokens[0], "fly") == 0)
      numProcs = fly(procs, tokens[1], tokens[2], numProcs);
    else if (strcmp(tokens[0], "showprocs") == 0)
      showprocs(procs, numProcs);
    else if (strcmp(tokens[0], "setdir") == 0)
      setdir(tokens[1]);
    else printf("No Command %s found.\n", tokens[0]);
  }

  return(0);

}
