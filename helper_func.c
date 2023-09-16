#include "shell.h"

void free_args(char **args);
char *get_process_id(void);
char *get_env_value(const char *variable);
void replace_variables(char **line, int *exit_status);

/**
 *  * free_args - Frees memory occupied by the arguments.
 *   * @args: A null-terminated array of strings.
 *    */
void free_args(char **args)
{
	    if (args == NULL)
		            return;

	        for (size_t i = 0; args[i] != NULL; i++)
			        free(args[i]);

		    free(args);
}

/**
 *  * get_process_id - Get the current process ID.
 *   *
 *    * Return: The current process ID as a string or NULL on failure.
 *     */
char *get_process_id(void)
{
	    pid_t pid = getpid();
	        char *pid_str = _itoa(pid);
		    return pid_str;
}

/**
 *  * get_env_value - Get the value of an environmental variable.
 *   * @variable: The name of the environmental variable.
 *    *
 *     * Return: The value of the environmental variable or an empty string if not found.
 *      */
char *get_env_value(const char *variable)
{
	    char *value = _getenv(variable);
	        return (value != NULL) ? _strdup(value) : _strdup("");
}

/**
 *  * replace_variables - Replace special variables in the command line.
 *   * @line: A pointer to the command line.
 *    * @exit_status: A pointer to the exit status of the last executed command.
 *     *
 *      * Description: Replaces $$ with the current process ID, $? with the exit
 *       * status, and environmental variables preceded by $ with their values.
 *        */
void replace_variables(char **line, int *exit_status)
{
	    char *new_line = NULL;
	        char *current = *line;
		    char *variable_start = NULL;
		        size_t new_size = 0;
			    size_t index = 0;

			        while (*current != '\0')
					    {
						            if (*current == '$')
								            {
										                if (*(current + 1) == '$')
													            {
															                    char *pid_str = get_process_id();
																	                    size_t pid_len = _strlen(pid_str);
																			                    new_size += pid_len;
																					                    new_line = _realloc(new_line, new_size, new_size + 1);
																							                    _strncpy(new_line + index, pid_str, pid_len);
																									                    index += pid_len;
																											                    free(pid_str);
																													                    current += 2;
																															                }
												            else if (*(current + 1) == '?')
														                {
																	                char *status_str = _itoa(*exit_status);
																			                size_t status_len = _strlen(status_str);
																					                new_size += status_len;
																							                new_line = _realloc(new_line, new_size, new_size + 1);
																									                _strncpy(new_line + index, status_str, status_len);
																											                index += status_len;
																													                free(status_str);
																															                current += 2;
																																	            }
													                else if (*(current + 1) == '\0' || *(current + 1) == ' ')
																            {
																		                    new_size++;
																				                    new_line = _realloc(new_line, new_size, new_size + 1);
																						                    new_line[index++] = '$';
																								                    current++;
																										                }
															            else
																	                {
																				                variable_start = current + 1;
																						                while (*current != '\0' && *current != ' ')
																									                    current++;

																								                size_t variable_len = current - variable_start;
																										                char *env_value = get_env_value(variable_start);
																												                size_t value_len = _strlen(env_value);

																														                new_size += value_len;
																																                new_line = _realloc(new_line, new_size, new_size + 1);
																																		                _strncpy(new_line + index, env_value, value_len);
																																				                index += value_len;

																																						                free(env_value);
																																								            }
																            }
							            else
									            {
											                new_size++;
													            new_line = _realloc(new_line, new_size, new_size + 1);
														                new_line[index++] = *current;
																            current++;
																	            }
								        }

				    new_line[index] = '\0';
				        free(*line);
					    *line = new_line;
}
