#include "shell.h"

char *read_command(int *exe_ret);
int execute_command(char *command, int *exe_ret);
int handle_commands(int *exe_ret);

/**
 *  * read_command - Reads a command from standard input.
 *   * @exe_ret: A pointer to the return value of the last executed command.
 *    *
 *     * Return: If an error occurs - NULL.
 *      *         Otherwise - a pointer to the read command.
 *       */
char *read_command(int *exe_ret)
{
	    size_t n = 0;
	        ssize_t read;
		    char *command = NULL;
		        char *prompt = "$ ";

			    if (command)
				            free(command);

			        read = _getline(&command, &n, STDIN_FILENO);

				    if (read == -1)
					            return (NULL);

				        if (read == 1)
						    {
							            hist++;
								            if (isatty(STDIN_FILENO))
										                write(STDOUT_FILENO, prompt, 2);
									            return (read_command(exe_ret));
										        }

					    command[read - 1] = '\0';
					        variable_replacement(&command, exe_ret);
						    handle_line(&command, read);

						        return (command);
}

/**
 *  * execute_command - Executes a single command.
 *   * @command: The command to execute.
 *    * @exe_ret: A pointer to the return value of the last executed command.
 *     *
 *      * Return: The exit status of the executed command.
 *       */
int execute_command(char *command, int *exe_ret)
{
	    int ret = 0;
	        char **args = _strtok(command, " ");
		    char **front = args;

		        if (!args)
				        return (ret);

			    if (check_args(args) != 0)
				        {
						        *exe_ret = 2;
							        free_args(args, args);
								        return (*exe_ret);
									    }

			        if (args[0])
					    {
						            int (*builtin)(char **args, char **front) = get_builtin(args[0]);

							            if (builtin)
									            {
											                ret = builtin(args + 1, front);
													            if (ret != EXIT)
															                    *exe_ret = ret;
														            }
								            else
										            {
												                *exe_ret = execute(args, front);
														            ret = *exe_ret;
															            }
									        }

				    hist++;

				        free_args(args, front);
					    return (ret);
}

/**
 *  * handle_commands - Reads, executes, and handles multiple commands.
 *   * @exe_ret: A pointer to the return value of the last executed command.
 *    *
 *     * Return: If an end-of-file is read - END_OF_FILE (-2).
 *      *         If an error occurs - -1.
 *       *         Otherwise - The exit status of the last executed command.
 *        */
int handle_commands(int *exe_ret)
{
	    int ret = 0;
	        char *command = NULL;

		    command = read_command(exe_ret);

		        if (!command)
				        return (END_OF_FILE);

			    char **commands = _strtok(command, ";");
			        free(command);

				    if (!commands)
					            return (ret);

				        for (size_t i = 0; commands[i]; i++)
						    {
							            ret = execute_command(commands[i], exe_ret);
								            if (ret == END_OF_FILE)
										            {
												                free_args(commands, commands);
														            return (END_OF_FILE);
															            }
									        }

					    free_args(commands, commands);
					        return (ret);
}
