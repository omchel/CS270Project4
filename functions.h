#define BUF_LEN 255
#define tokDelim " -"

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

struct newVar {

  char name[BUF_LEN];
  char valStr[BUF_LEN];

};

struct proc {

  int pID;
  char pName[BUF_LEN];

};

void run(char* cmd, char* param, int numTokens) {

  if (numTokens < 3)
    printf("Not enough tokens to run\n");
  else{

  	pid_t pid;
  	int* status;

  	char* args[BUF_LEN] = {cmd, param, NULL};
  	pid = fork();
  	if (pid == 0)
  		execvp(args[0],args);
  	else
  		waitpid(pid, status, 0);

  }

}

int fly(struct proc* processes, char* cmd, char* param, int numProcs) {

	pid_t pid;
	int status[BUF_LEN];

	char* args[BUF_LEN] = {cmd, param, NULL};
	pid = fork();
	if (pid == 0)
		execvp(args[0],args);
	else{
		strcpy(processes[numProcs].pName,args[0]);
		processes[numProcs].pID =  pid;
    numProcs++;
	}

  return numProcs;

}

void showprocs(struct proc* procs, int numProcs) {

  if (numProcs <= 0)
    printf("No background processes running.\n");
  else{
  	printf("Background processes:\n");

  	for (int i = 0; i < numProcs; i++) {

  		printf("\t%s\n", procs[i].pName);

  	}

  }

}

struct newVar setvar(char** tokens, struct newVar* vars, int *numVars) {

  struct newVar createdVar;
  strcpy(createdVar.name, tokens[1]);
  strcpy(createdVar.valStr, tokens[2]);
  *numVars+=1;

  return createdVar;

}

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
			cwd[strlen(cwd)] = '/';
			dirName = strcat(cwd,dirName); // append the cwd and the relative path name
			printf("dirName = %s\n", dirName);
			if (chdir(dirName) != 0)
			    perror("chdir() error()");
			else {
			    if (getcwd(nwd, sizeof(nwd)) == NULL) // check if the change in cwd failed
			      perror("getcwd() error");
			    else
			      printf("New working directory is: %s\n", nwd);
			  }
			}
	}
}

void exitShell(char** tokens, int numTokens) {

  if (numTokens > 2) printf("Too many tokens to done.\n");
  else if(numTokens == 1) exit(0);
  else {

    int exitNum = atoi(tokens[1]);

    if (strcmp(tokens[1], "0") == 0 || tokens[1] == NULL)
      exit(0);
    else{

      if (exitNum == 0 || exitNum < 0) printf("Parameter to done must be a non-negative integer.\n");
      else exit(exitNum);

    }

  }

}

void tovar(char*varName, char* cmd, char* param) {

  pid_t pid;
  int* status;

  char* args[BUF_LEN] = {cmd, param, NULL};
  pid = fork();
  if (pid == 0)
    execvp(args[0],args);
  else
    waitpid(pid, status, 0);

}
