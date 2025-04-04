#include <stdio.h>
#include <stdlib.h>
#include <spawn.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#define N 12

extern char **environ;

char *allowed[N] = {"cp","touch","mkdir","ls","pwd","cat","grep","chmod","diff","cd","exit","help"};

// return 1 if cmd is one of the allowed commands
// return 0 otherwise
int isAllowed(const char*cmd) {
	for(int i = 0; i < N; i++){
		if(strcmp(cmd, allowed[i]) == 0) return 1;
	}
	return 0;
}

// copy a file to another directory
void command_cp(char* args[], int argc){
}
// add a new file
void command_touch(char* args[], int argc){
}

// make a new directory
void command_mkdir(char* args[], int argc){
}

// list items in current directory
void command_ls(char* args[], int argc){
}

// print the current directory
void command_pwd(char* args[], int argc){
}

// read a file
void command_cat(char* args[], int argc){
}

// search for files or lines of code
void command_grep(char* args[], int argc){
}

// change permissions of a file or directory
void command_chmod(char* args[], int argc){
}

// show the difference between two files
void command_diff(char* args[], int argc){
}

// change into the specified directory
void command_cd(char* args[], int argc){
	// if command is more than "cd path/to/dir", fail
	if(argc > 2){
		printf("cd error: too many arguments");
	}
	else if(chdir(args[1]) != 0){
		printf("cd error: directory \"%s\" not found", args[1]);
	}
}

// exit the restricted shell
void command_exit(char* args[], int argc){
	exit(EXIT_SUCCESS);// exit the program with success
}

// list all possible commands
void command_help(char* args[], int argc){
	printf("1: cp\n 2: touch\n 3: mkdir\n 4: ls\n 5: pwd\n 6: cat\n 7: grep\n 8: chmod\n 9: diff\n 10: cd\n 11: exit\n 12: help\n");
}

int main() {
    char line[256];
	char line_copy[256]; // for strtok
	char* argv[20]; // for command line arguments

    while (1) {

	fprintf(stderr,"rsh>");

	if (fgets(line,256,stdin)==NULL) continue;

	if (strcmp(line,"\n")==0) continue;

	line[strlen(line)-1]='\0';

	// create a copy of line so line is not changed by strtok
	strcpy(line_copy, line);
	char* command = strtok(line_copy, " ");

	// populate argv with the rest of the arguments
	char* current_arg;
	int index = 1; // 1 because argv[0] is already set to the command
	current_arg = strtok(NULL, " ");
	while (current_arg != NULL) {
		argv[index] = malloc(strlen(current_arg) + 1); // allocate memory for each argument
		strcpy(argv[index], current_arg);
		index++;
		current_arg = strtok(NULL, " ");
	}
	argv[index] = NULL; // make sure array is NULL terminated
	
	// handle each command appropriately
	if(isAllowed(command) == 0) printf("NOT ALLOWED!");
	else if(strcmp(command, "cp") == 0) command_cp(argv, index);
	else if(strcmp(command, "touch") == 0) command_touch(argv, index);
	else if(strcmp(command, "mkdir") == 0) command_mkdir(argv, index);
	else if(strcmp(command, "ls") == 0) command_ls(argv, index);
	else if(strcmp(command, "pwd") == 0) command_pwd(argv, index);
	else if(strcmp(command, "cat") == 0) command_cat(argv, index);
	else if(strcmp(command, "grep") == 0) command_grep(argv, index);
	else if(strcmp(command, "chmod") == 0) command_chmod(argv, index);
	else if(strcmp(command, "diff") == 0) command_diff(argv, index);
	else if(strcmp(command, "cd") == 0) command_cd(argv, index);
	else if(strcmp(command, "exit") == 0) command_exit(argv, index);
	else if(strcmp(command, "help") == 0) command_help(argv, index);
    }

    return 0;
}
