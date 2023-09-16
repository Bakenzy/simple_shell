#include "shell.h"

int (*findShellbyBuiltin(char *command))(char **args, char **front);
int executeExit(char **args, char **front);
int executeChangeDirectory(char **args, char __attribute__((__unused__)) **front);
int executeHelp(char **args, char __attribute__((__unused__)) **front);

/**
 *  * findShellbyBuiltin - Matches a command with a corresponding
 *   *                     shellby builtin function.
 *    * @command: The command to match.
 *     *
 *      * Return: A function pointer to the corresponding builtin.
 *       */
int (*findShellbyBuiltin(char *command))(char **args, char **front)
{
	    builtin_t builtinFunctions[] = {
		            { "exit", executeExit },
			            { "env", executeEnv },
				            { "setenv", executeSetenv },
					            { "unsetenv", executeUnsetenv },
						            { "cd", executeChangeDirectory },
							            { "alias", executeAlias },
								            { "help", executeHelp },
									            { NULL, NULL }
			        };
	        int i;

		    for (i = 0; builtinFunctions[i].name; i++)
			        {
					        if (_strcmp(builtinFunctions[i].name, command) == 0)
							            break;
						    }
		        return (builtinFunctions[i].func);
}

/**
 *  * executeExit - Terminates the shellby process.
 *   * @args: Array of arguments, can include an exit value.
 *    * @front: Double pointer to the beginning of args.
 *     *
 *      * Return: If no arguments - -3.
 *       *         If the exit value is invalid - 2.
 *        *         Otherwise - Exits with the given status.
 *         *
 *          * Description: When returning -3, the program exits back in the main function.
 *           */
int executeExit(char **args, char **front)
{
	    int i, intLength = 10;
	        unsigned int exitStatus = 0, maxInt = 1U << (sizeof(int) * 8 - 1);

		    if (args[0])
			        {
					        if (args[0][0] == '+')
							        {
									            i = 1;
										                intLength++;
												        }
						        for (; args[0][i]; i++)
								        {
										            if (i <= intLength && args[0][i] >= '0' && args[0][i] <= '9')
												                    exitStatus = (exitStatus * 10) + (args[0][i] - '0');
											                else
														                return (createError(--args, 2));
													        }
							    }
		        else
				    {
					            return (-3);
						        }
			    if (exitStatus > maxInt - 1)
				            return (createError(--args, 2));
			        args -= 1;
				    freeArgs(args, front);
				        freeEnvironment();
					    freeAliasList(aliases);
					        exit(exitStatus);
}

/**
 *  * executeChangeDirectory - Changes the current directory of the shellby process.
 *   * @args: Array of arguments.
 *    * @front: Double pointer to the beginning of args.
 *     *
 *      * Return: If the provided path is not a directory - 2.
 *       *         If an error occurs - -1.
 *        *         Otherwise - 0.
 *         */
int executeChangeDirectory(char **args, char __attribute__((__unused__)) **front)
{
	    char **dirInfo, *newLine = "\n";
	        char *oldPwd = NULL, *pwd = NULL;
		    struct stat directory;

		        oldPwd = getcwd(oldPwd, 0);
			    if (!oldPwd)
				            return (-1);

			        if (args[0])
					    {
						            if (*(args[0]) == '-' || _strcmp(args[0], "--") == 0)
								            {
										                if ((args[0][1] == '-' && args[0][2] == '\0') || args[0][1] == '\0')
													            {
															                    if (_getenv("OLDPWD") != NULL)
																		                        (chdir(*_getenv("OLDPWD") + 7));
																	                }
												            else
														                {
																	                free(oldPwd);
																			                return (createError(args, 2));
																					            }
													            }
							            else
									            {
											                if (stat(args[0], &directory) == 0 && S_ISDIR(directory.st_mode)
															                && ((directory.st_mode & S_IXUSR) != 0))
														                chdir(args[0]);
													            else
															                {
																		                free(oldPwd);
																				                return (createError(args, 2));
																						            }
														            }
								        }
				    else
					        {
							        if (_getenv("HOME") != NULL)
									            chdir(*(_getenv("HOME")) + 5);
								    }

				        pwd = getcwd(pwd, 0);
					    if (!pwd)
						            return (-1);

					        dirInfo = malloc(sizeof(char *) * 2);
						    if (!dirInfo)
							            return (-1);

						        dirInfo[0] = "OLDPWD";
							    dirInfo[1] = oldPwd;
							        if (executeSetenv(dirInfo, dirInfo) == -1)
									        return (-1);

								    dirInfo[0] = "PWD";
								        dirInfo[1] = pwd;
									    if (executeSetenv(dirInfo, dirInfo) == -1)
										            return (-1);
									        if (args[0] && args[0][0] == '-' && args[0][1] != '-')
											    {
												            write(STDOUT_FILENO, pwd, _strlen(pwd));
													            write(STDOUT_FILENO, newLine, 1);
														        }
										    free(oldPwd);
										        free(pwd);
											    free(dirInfo);
											        return (0);
}

/**
 *  * executeHelp - Displays information about shellby builtin commands.
 *   * @args: Array of arguments.
 *    * @front: Pointer to the beginning of args.
 *     *
 *      * Return: If an error occurs - -1.
 *       *         Otherwise - 0.
 *        */
int executeHelp(char **args, char __attribute__((__unused__)) **front)
{
	    if (!args[0])
		            helpAll();
	        else if (_strcmp(args[0], "alias") == 0)
			        helpAlias();
		    else if (_strcmp(args[0], "cd") == 0)
			            helpCd();
		        else if (_strcmp(args[0], "exit") == 0)
				        helpExit();
			    else if (_strcmp(args[0], "env") == 0)
				            helpEnv();
			        else if (_strcmp(args[0], "setenv") == 0)
					        helpSetenv();
				    else if (_strcmp(args[0], "unsetenv") == 0)
					            helpUnsetenv();
				        else if (_strcmp(args[0], "help") == 0)
						        helpHelp();
					    else
						            write(STDERR_FILENO, shellName, _strlen(shellName));

					        return (0);
}
