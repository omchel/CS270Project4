/*
  CS270Project4
  Systems Programming Project 4

  Authors: Kenton Carrier and Chelina Ortiz Montanez
*/

#define BUF_LEN 255
#define tokDelim " -"

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
// Structure used to save the tokens 
// created with setvar function
struct newVar {

  char name[BUF_LEN];
  char valStr[BUF_LEN];

};
// Structure used to save the Process
// IDs (PIDs) of the procedures
struct proc {

  int pID;
  char pName[BUF_LEN];

};
/* run function:
  The user submits a run command to execute a 
  program.  
  msh should wait for the program to finish 
  before it prompts for and accepts the next command.
*/
void run(char* cmd, char* param, int numTokens) {

  if (numTokens < 3) // check if we have the correct amount of tokens
    printf("Not enough tokens to run\n");
  else{

  	pid_t pid; 
  	int* status;

  	char* args[BUF_LEN] = {cmd, param, NULL};
  	pid = fork(); //fork() creates a child process and saves it as a PID
  	if (pid == 0) // check if the PID is zero
  		execvp(args[0],args); // child process is run
  	else // if the PID is not zero
  		waitpid(pid, status, 0); // the parent is running and waits for child process to stop running

  }

}
/* fly function;
  The fly command is identical to the run command, 
  except that the process running the command should 
  be in the background, that is, msh should immediately 
  prompt for and accept the next command.
*/
int fly(struct proc* processes, char* cmd, char* param, int numProcs) {

	pid_t pid;
	int status[BUF_LEN];

	char* args[BUF_LEN] = {cmd, param, NULL};
	if (pid == 0) // check if the PID is zero
      execvp(args[0],args); // child process is run
    else { // if the PID is not zero
		strcpy(processes[numProcs].pName,args[0]);  // populate the structure with the information of the processes
		processes[numProcs].pID =  pid;             // running in the background.
    numProcs++;
	}

  return numProcs;

}
/* showprocs function:
  msh lists all processes running in the background, 
  in any format you like. msh should keep a list and 
  not rely on external programs like ps to create its 
  output.
*/
void showprocs(struct proc* procs, int numProcs) {
  // using the number of processes found with the fly function
  if (numProcs <= 0) // check if there are no processes running in the background
    printf("No background processes running.\n");
  else{ // if there were processes found running on the background
  	printf("Background processes:\n");

  	for (int i = 0; i < numProcs; i++) {

  		printf("\t%s\n", procs[i].pName); // print each process stored in the structure

  	}

  }

}
/* servar function:
  Here, variable is any reasonable variable name 
  (starting with a letter, continuing with letters or 
  numbers), and value is a token. Variable names are 
   case-sensitive. The effect of this command is to 
   associate the variable name with the given value 
   in a data structure inside msh.
*/
struct newVar setvar(char** tokens, struct newVar* vars, int *numVars) {

  struct newVar createdVar;
  strcpy(createdVar.name, tokens[1]); // copy the first token given to the name of the element in the structure
  strcpy(createdVar.valStr, tokens[2]); //copu the second token given to the value of the element
  *numVars+=1; // increase the count of variables stored by one

  return createdVar;

}
/* setdir function;
  This command changes the current directory to 
  directoryName. See the getwd(3) and chdir(2) system
   calls. the required parameter directoryName may be 
   either absolute (starting with /) or relative (not 
   starting with /).
*/
void setdir(char dirName[]) {
	char cwd[BUF_LEN];
	char nwd[BUF_LEN];
	if (dirName[0] == '/') { //check if we have an absolute path
	  if (chdir(dirName) != 0) //if we fail changing the current working directory
	    perror("chdir() error()"); //print proper error message
	  else { //changed the cwd successfully
	    if (getcwd(cwd, sizeof(cwd)) == NULL) //check if getting the cwd failed
	      perror("getcwd() error"); //print proper error message
	    else
	      printf("current working directory is: %s\n", cwd); // print new cwd
	  }
	} else { // if we have a relative parameter in dirName
		if (getcwd(cwd, sizeof(cwd)) != NULL) { // if we successfully retrived cwd
			fprintf(stdout, "Current working dir: %s\n", cwd);
			cwd[strlen(cwd)] = '/'; // add the character '/' to the end of the cwd
			dirName = strcat(cwd,dirName); // append the cwd and the relative path name
			printf("dirName = %s\n", dirName);
			if (chdir(dirName) != 0) //if we fail changing the current working directory
        perror("chdir() error()"); //print proper error message
      else { //changed the cwd successfully
        if (getcwd(nwd, sizeof(nwd)) == NULL) //check if getting the  new wd failed
          perror("getcwd() error"); //print proper error message
        else
          printf("current working directory is: %s\n", nwd); // print new wd
			}
	}
}
/* exit function:
  msh exits. If the value parameter is present, it must
   be a non-negative integer, in which case msh uses that 
   integer as its exit status. If the parameter is absent, 
   msh exits with status 0. msh also accepts <control-D> 
   (end-of-file) on the input stream and treats it like 
   done 0.
*/
void exitShell(char** tokens, int numTokens) {
  // check how many tokens are active
  if (numTokens > 2) printf("Too many tokens to done.\n");
  else if(numTokens == 1) exit(0);
  else { // if there are less than 1 active tokens

    int exitNum = atoi(tokens[1]); // atoi() converts an int variable  into a string

    if (strcmp(tokens[1], "0") == 0 || tokens[1] == NULL) // if there are no tokens left
      exit(0);
    else{ // if there are still any active tokens
      if (exitNum == 0 || exitNum < 0) printf("Parameter to done must be a non-negative integer.\n");
      else exit(exitNum);

    }

  }

}
/* tovar function:
  The tovar command executes the program cmd along with 
  its parameters, if any, just like the run command. 
  However, msh absorbs the standard output of the program 
  and assigns it as the value of variable specified by the 
  second token.
*/
void tovar(char*varName, char* cmd, char* param) {

  pid_t pid;
  int* status;

  char* args[BUF_LEN] = {cmd, param, NULL};
  pid = fork(); //fork() creates a child process and saves it as a PID
    if (pid == 0) // check if the PID is zero
      execvp(args[0],args); // child process is run
    else // if the PID is not zero
      waitpid(pid, status, 0); // the parent is running and waits for child process to stop running
}
