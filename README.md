# CS270Project4
Systems Programming Project 4

Authors: Kenton Carrier and Chelina Ortiz Montanez

Project Description;
	The project MyShell (msh) is a functioning shell that allows user to interact with it by creating variables and running commands. 
	Using tokens to receive the user input and parse through it, we can execute the commands requested and have multiple processes running at a time.

Algorithms Used:
	 We did not use any pre-defined algorithms for the implementation of this code

Limitations/Known Bugs: 
	- We could ot find a proper way to reset a variable-s value
	- The 'tovar' function has a lot of bugs and its not set properly
	- The variable 'showVariables' has no implementation
	- If we input the name of a variable without the  ^, it will still substitute
	- The 'setdir' function crashes unexpectedly, but works fine sometimes
