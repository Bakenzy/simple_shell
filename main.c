#include "shell.h"

void handle_signal(int signal);
int execute_command(char **arguments, char **command_front);

/**
 *  * handle_signal - Signal handler to print a new prompt.
 *   * @signal: The signal received.
 *    */
void handle_signal(int signal)
{
	    char *new_prompt = "\n$ ";

	        (void)signal;
		    signal(SIGINT, handle_signal);
		        write(STDIN_FILENO, new_prompt, 3);
}

/**
 *  * execute_command - Executes a command in a child process.
 *   * @arguments: An array of command arguments.
 *    * @command_front: A pointer to the first argument in the array.
 *     *
 *      * Return: If an error occurs - the corresponding error code.
 *       *         Otherwise - the exit value of the last executed command.
 *        */
int execute_command(char **arguments, char **command_front)
{
	    pid_t child_pid;
	        int status, flag = 0, exit_code = 0;
		    char *command = arguments[0];

		        if (command[0] != '/' && command[0] != '.')
				    {
					            flag = 1;
						            command = get_location(command);
							        }

			    if (!command || (access(command, F_OK) == -1))
				        {
						        if (errno == EACCES)
								            exit_code = create_error(arguments, 126);
							        else
									            exit_code = create_error(arguments, 127);
								    }
			        else
					    {
						            child_pid = fork();
							            if (child_pid == -1)
									            {
											                if (flag)
														                free(command);
													            perror("Error child:");
														                return 1;
																        }
								            if (child_pid == 0)
										            {
												                execve(command, arguments, environ);
														            if (errno == EACCES)
																                    exit_code = create_error(arguments, 126);
															                free_env();
																	            free_arguments(arguments, command_front);
																		                free_alias_list(aliases);
																				            _exit(exit_code);
																					            }
									            else
											            {
													                wait(&status);
															            exit_code = WEXITSTATUS(status);
																            }
										        }
				    if (flag)
					            free(command);
				        return exit_code;
}

/**
 *  * main - A simple UNIX command interpreter.
 *   * @argc: The number of arguments supplied to the program.
 *    * @argv: An array of pointers to the arguments.
 *     *
 *      * Return: The return value of the last executed command.
 *       */
int main(int argc, char *argv[])
{
	    int exit_code = 0, ret;
	        int *execution_result = &ret;
		    char *prompt = "$ ", *new_line = "\n";

		        name = argv[0];
			    hist = 1;
			        aliases = NULL;
				    signal(SIGINT, handle_signal);

				        *execution_result = 0;
					    environ = copy_environment();
					        if (!environ)
							        exit(-100);

						    if (argc != 1)
							        {
									        exit_code = process_file_commands(argv[1], execution_result);
										        free_env();
											        free_alias_list(aliases);
												        return *execution_result;
													    }

						        if (!isatty(STDIN_FILENO))
								    {
									            while (exit_code != END_OF_FILE && exit_code != EXIT)
											                exit_code = handle_arguments(execution_result);
										            free_env();
											            free_alias_list(aliases);
												            return *execution_result;
													        }

							    while (1)
								        {
										        write(STDOUT_FILENO, prompt, 2);
											        exit_code = handle_arguments(execution_result);
												        if (exit_code == END_OF_FILE || exit_code == EXIT)
														        {
																            if (exit_code == END_OF_FILE)
																		                    write(STDOUT_FILENO, new_line, 1);
																	                free_env();
																			            free_alias_list(aliases);
																				                exit(*execution_result);
																						        }
													    }

							        free_env();
								    free_alias_list(aliases);
								        return *execution_result;
}
