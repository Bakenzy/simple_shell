#include "shell.h"

int file_open_error(char *file_path);
int process_file_commands(char *file_path, int *execution_result);

/**
 *  * file_open_error - Prints a "can't open" error message when a file cannot be opened.
 *   * @file_path: The path to the file.
 *    *
 *     * Return: The error code 127.
 *      */
int file_open_error(char *file_path)
{
	    char *error_message;
	        int error_message_length;

		    char *history_count_str = _itoa(hist);
		        if (!history_count_str)
				        return 127;

			    error_message_length = _strlen(name) + _strlen(history_count_str) + _strlen(file_path) + 16;
			        error_message = malloc(sizeof(char) * (error_message_length + 1));
				    if (!error_message)
					        {
							        free(history_count_str);
								        return 127;
									    }

				        _strcpy(error_message, name);
					    _strcat(error_message, ": ");
					        _strcat(error_message, history_count_str);
						    _strcat(error_message, ": Can't open ");
						        _strcat(error_message, file_path);
							    _strcat(error_message, "\n");

							        free(history_count_str);
								    write(STDERR_FILENO, error_message, error_message_length);
								        free(error_message);

									    return 127;
}

/**
 *  * process_file_commands - Reads and executes commands from a file.
 *   * @file_path: The path to the file.
 *    * @execution_result: A pointer to store the return value of the last command.
 *     *
 *      * Return: If the file couldn't be opened - 127.
 *       *         If memory allocation fails - -1.
 *        *         Otherwise, the return value of the last executed command.
 *         */
int process_file_commands(char *file_path, int *execution_result)
{
	    ssize_t file, bytes_read, i;
	        unsigned int line_size = 0;
		    unsigned int old_size = 120;
		        char *line, **args, **front;
			    char buffer[120];
			        int ret;

				    hist = 0;
				        file = open(file_path, O_RDONLY);
					    if (file == -1)
						        {
								        *execution_result = file_open_error(file_path);
									        return *execution_result;
										    }

					        line = malloc(sizeof(char) * old_size);
						    if (!line)
							            return -1;

						        do
								    {
									            bytes_read = read(file, buffer, 119);
										            if (bytes_read == 0 && line_size == 0)
												                return *execution_result;

											            buffer[bytes_read] = '\0';
												            line_size += bytes_read;
													            line = _realloc(line, old_size, line_size);
														            _strcat(line, buffer);
															            old_size = line_size;
																        } while (bytes_read);

							    for (i = 0; line[i] == '\n'; i++)
								            line[i] = ' ';

							    for (; i < line_size; i++)
								        {
										        if (line[i] == '\n')
												        {
														            line[i] = ';';
															                for (i += 1; i < line_size && line[i] == '\n'; i++)
																		                line[i] = ' ';
																	        }
											    }

							        variable_replacement(&line, execution_result);
								    handle_line(&line, line_size);
								        args = _strtok(line, " ");
									    free(line);

									        if (!args)
											        return 0;

										    if (validate_args(args) != 0)
											        {
													        *execution_result = 2;
														        free_args(args, args);
															        return *execution_result;
																    }

										        front = args;

											    for (i = 0; args[i]; i++)
												        {
														        if (_strncmp(args[i], ";", 1) == 0)
																        {
																		            free(args[i]);
																			                args[i] = NULL;
																					            ret = call_args(args, front, execution_result);
																						                args = &args[++i];
																								            i = 0;
																									            }
															    }

											        ret = call_args(args, front, execution_result);

												    free(front);
												        return ret;
}
