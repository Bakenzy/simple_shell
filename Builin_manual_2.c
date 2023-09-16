#include "shell.h"

void displayEnvHelp(void);
void displaySetenvHelp(void);
void displayUnsetenvHelp(void);

/**
 *  * displayEnvHelp - Displays information about the 'env' command.
 *   */
void displayEnvHelp(void)
{
	    char *message = "env: env\n";
	        write(STDOUT_FILENO, message, _strlen(message));
		    message = "\tDisplays the current environment.\n";
		        write(STDOUT_FILENO, message, _strlen(message));
}

/**
 *  * displaySetenvHelp - Displays information about the 'setenv' command.
 *   */
void displaySetenvHelp(void)
{
	    char *message = "setenv: setenv [VARIABLE] [VALUE]\n";
	        write(STDOUT_FILENO, message, _strlen(message));
		    message = "\tInitializes a new environment variable or modifies an existing one.\n";
		        write(STDOUT_FILENO, message, _strlen(message));
			    message = "\tPrints an error message to stderr upon failure.\n";
			        write(STDOUT_FILENO, message, _strlen(message));
}

/**
 *  * displayUnsetenvHelp - Displays information about the 'unsetenv' command.
 *   */
void displayUnsetenvHelp(void)
{
	    char *message = "unsetenv: unsetenv [VARIABLE]\n";
	        write(STDOUT_FILENO, message, _strlen(message));
		    message = "\tRemoves an environmental variable.\n";
		        write(STDOUT_FILENO, message, _strlen(message));
			    message = "\tPrints an error message to stderr upon failure.\n";
			        write(STDOUT_FILENO, message, _strlen(message));
}
