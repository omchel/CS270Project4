
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <regex.h>

#define VARLENGTH 255
/* setvar variable value
	Here, variable is any reasonable variable name 
	(starting with a letter, continuing with letters 
	or numbers), and value is a token. It is conventional 
	for users to represent variables in ALL CAPITALS, but 
	msh does not enforce this convention. Variable names 
	are case-sensitive, that is, home and HOME represent 
	different variables. You may limit the length of the 
	content of variables to 255 characters. The effect of 
	this command is to associate the variable name with 
	the given value in a data structure inside msh.
*/
/*void setvar(char* varName, char* val){
	regex_t exp;
	char msgbuf[100];
	char var1Letter = regcomp(&exp, "-?[a-zA-z]", 1); //regular expression (A-Z, locks sensitive)
	if (!var1Letter){//check if there is the first thing in the variable name is a letter (if it matches)
		var1Letter = regex(&exp, varName, 0, NULL, 0);
		if (!var1Letter){
			if (sizeOf(val) < VARLENGTH){
				setenv varName  val;
				printf("Variable created: %s, %s", varName, val);
			}
		} else if (var1Letter) {
			printf("The variable name must start with a letter.\n");
		} else {
			regerror(reti, &regex, msgbuf, sizeof(msgbuf));
			fprintf(stderr, "Regex match failed: %s\n", msgbuf);
			exit(1);
		}
	}
}
/* setprompt newPrompt
	Set the shell prompt to newPrompt, which is a token. Do not 
	add or subtract spaces at the end of the new prompt. The 
	initial prompt in msh is msh > . (There is a space after the
	 >.)

/* setdir directoryName
	This command changes the current directory to directoryName. 
	See the getwd(3) and chdir(2) system calls. the required 
	parameter directoryName may be either absolute (starting with /) 
	or relative (not starting with /). 
*/
void setdir(char dirName[]) {
	char cwd[VARLENGTH];
	char nwd[VARLENGTH];
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
/* showprocs
	msh lists all processes running in the background, in any
	 format you like. msh should keep a list and not rely on 
	 external programs like ps to create its output.
*/
void showprocs() {
// to keep the pids of the created childs?	
}
/*done value
	msh exits. If the value parameter is present, it must be 
	a non-negative integer, in which case msh uses that integer 
	as its exit status. If the parameter is absent, msh exits 
	with status 0. msh also accepts <control-D> (end-of-file) 
	on the input stream and treats it like done 0.
*/
/*void done(int param){
	int status = 0;
	if (param < 0) {
		status = param;
	}
	exit(1);
}

/* run cmd [param ... ]
	(The brackets indicate "optional" and the dots indicate "and 
	more if desired".) The user submits a run command to execute 
	a program. The keyword run must appear as the first token on 
	the command line, followed by the command to be executed: 
	cmd is a token that specifies the filename of the program the 
	ser wants to execute. It is followed by zero or more tokens 
	specifying parameters. msh should wait for the program to 
	finish before it prompts for and accepts the next command.
*/
void run(char* cmd, char* param) {
	char* args[] = {cmd, param, NULL};
	execvp(args[0],args);
//	waitpid();
}
/*fly cmd [param ... ]
	The fly command is identical to the run command, except that
	the process running the command should be in the background, 
	that is, msh should immediately prompt for and accept the 
	next command.
*/
/*void fly(char* cmd, char* param) {
	pid_t pid;
	pid = fork();
}

/*tovar variable cmd [param ... ]
	The tovar command executes the program cmd along with its 
	parameters, if any, just like the run command. However, msh 
	absorbs the standard output of the program and assigns it as 
	the value of variable specified by the second token.
*/
/*void tovar(char* varName, char* cmd) {
	char* args[] = {varName, cmd, NULL];
	execvp(args[0],args);
//	waitpid();
}*/

int main(){
	//run("ls", "-la");
	setdir("empty");
	printf("\n");
	setdir("/home/cor228");
//	run("ls", "-a");
//	setvar("Variable","20");
	
	return 0;
}
