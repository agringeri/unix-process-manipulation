Anthony Gringeri

Project 1

CS3013, Operating Systems, Professor Craig Wills

This project introduces the process manipulation facilites in the Unix/Linux Operating System.
Contained is the program 'doit' which takes another command as an argument and executes that command.
After the command is carried out and all processes are exited successfully, 
	doit prints out various statistics about the processes.
To compile, point shell to directory containing all files and use 'make' command to compile.
To run, use ./doit [command].

For example, 
==> ./doit sleep 3
	will carry out the command sleep with an argument of 3

