#include "shell.h"

char *generatePermissionDeniedError(char **args);
char *generateCommandNotFoundError(char **args);

/**
 *  * generatePermissionDeniedError - Generates an error message for permission denied failures.
 *   * @args: An array of arguments passed to the command.
 *    *
 *     * Return: The error message string.
 *      */
char *generatePermissionDeniedError(char **args)
{
	    char *error;
	        int len;

		    len = _strlen(name) + _strlen(args[0]) + 24;
		        error = malloc(sizeof(char) * (len + 1));
			    if (!error)
				            return NULL;

			        _strcpy(error, name);
				    _strcat(error, ": ");
				        _strcat(error, args[0]);
					    _strcat(error, ": Permission denied\n");

					        return error;
}

/**
 *  * generateCommandNotFoundError - Generates an error message for command not found failures.
 *   * @args: An array of arguments passed to the command.
 *    *
 *     * Return: The error message string.
 *      */
char *generateCommandNotFoundError(char **args)
{
	    char *error;
	        int len;

		    len = _strlen(name) + _strlen(args[0]) + 16;
		        error = malloc(sizeof(char) * (len + 1));
			    if (!error)
				            return NULL;

			        _strcpy(error, name);
				    _strcat(error, ": ");
				        _strcat(error, args[0]);
					    _strcat(error, ": not found\n");

					        return error;
}
