#include "shell.h"

char *generateEnvError(char **args);
char *generateAliasNotFoundError(char **args);
char *generateExitError(char **args);
char *generateCdError(char **args);
char *generateSyntaxError(char **args);

/**
 * generateEnvError - Generates an error message for shellby_env errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error message string.
 */
char *generateEnvError(char **args)
{
	char *error;
	int len;

	len = _strlen(name) + _strlen(args[0]) + 45;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": Unable to add/remove from environment\n");

	return (error);
}

/**
 * generateAliasNotFoundError - Generates an error message for shellby_alias errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error message string.
 */
char *generateAliasNotFoundError(char **args)
{
	char *error;
	int len;

	len = _strlen(name) + _strlen(args[0]) + 13;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		return (NULL);
	}

	_strcpy(error, "alias: ");
	_strcat(error, args[0]);
	_strcat(error, " not found\n");

	return (error);
}

/**
 * generateExitError - Generates an error message for shellby_exit errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error message string.
 */
char *generateExitError(char **args)
{
	char *error;
	int len;

	len = _strlen(name) + _strlen(args[0]) + 27;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": exit: Illegal number: ");
	_strcat(error, args[0]);
	_strcat(error, "\n");

	return (error);
}

/**
 * generateCdError - Generates an error message for shellby_cd errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error message string.
 */
char *generateCdError(char **args)
{
	char *error;
	int len;

	len = _strlen(name) + _strlen(args[0]) + 24;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		return (NULL);
	}

	_strcpy(error, name);
	if (args[0][0] == '-')
	{
		_strcat(error, ": cd: Illegal option ");
	}
	else
	{
		_strcat(error, ": cd: can't cd to ");
	}
	_strcat(error, args[0]);
	_strcat(error, "\n");

	return (error);
}

/**
 * generateSyntaxError - Generates an error message for syntax errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error message string.
 */
char *generateSyntaxError(char **args)
{
	char *error;
	int len;

	len = _strlen(name) + _strlen(args[0]) + 33;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": Syntax error: \"");
	_strcat(error, args[0]);
	_strcat(error, "\" unexpected\n");

	return (error);
}

