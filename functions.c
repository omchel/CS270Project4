#include <string>
#include <stdlib>
#include <unistd.h>

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
void setvar(string varName, int val){
	if (varName[0] =! ){//check if there is the first thing in the variable name is a letter
		return;
	} 
	if (val > VARLENGTH){
		return;
	}
	int varName = val;
}
/* setprompt newPrompt
	Set the shell prompt to newPrompt, which is a token. Do not 
	add or subtract spaces at the end of the new prompt. The 
	initial prompt in msh is msh > . (There is a space after the
	 >.)
*/
/* setdir directoryName
	This command changes the current directory to directoryName. 
	See the getwd(3) and chdir(2) system calls. the required 
	parameter directoryName may be either absolute (starting with /) 
	or relative (not starting with /). 
*/
void setdir(string dirName) {
	if (dirName[0] == "/") { //check if dirName is an absolute parameter
		chdir(dirName);
	} else { // if we have a relative parameter in dirName
		char *getwd(char *path_name);
		dirName = path_name + dirName;
		chdir(dirName);
	}
}
/* showprocs
	msh lists all processes running in the background, in any
	 format you like. msh should keep a list and not rely on 
	 external programs like ps to create its output.
*/
void showprocs() {

}
/*done value
	msh exits. If the value parameter is present, it must be 
	a non-negative integer, in which case msh uses that integer 
	as its exit status. If the parameter is absent, msh exits 
	with status 0. msh also accepts <control-D> (end-of-file) 
	on the input stream and treats it like done 0.
*/

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
void run(int param, string param1) {

}
/*fly cmd [param ... ]
	The fly command is identical to the run command, except that
	the process running the command should be in the background, 
	that is, msh should immediately prompt for and accept the 
	next command.
*/
 void fly(string command) {

 }
/*
tovar variable cmd [param ... ]
	The tovar command executes the program cmd along with its 
	parameters, if any, just like the run command. However, msh 
	absorbs the standard output of the program and assigns it as 
	the value of variable specified by the second token.
*/
void tovar(string varName, string command) {

}