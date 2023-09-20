#include "shell.h"

void handle_line(char **line);
ssize_t get_new_len(char *line);
void replace_logical_ops(char *line, ssize_t *new_len);

/**
 *  * handle_line - Process a line read from standard input.
 *   * @line: A pointer to a line read from standard input.
 *    *
 *     * Description: Inserts spaces to separate ";", "||", and "&&".
 *      *              Replaces "#" with '\0'.
 *       */
void handle_line(char **line)
{
	    ssize_t new_len = get_new_len(*line);
	        if (new_len != -1)
			    {
				            char *new_line = malloc(new_len + 1);
					            if (new_line)
							            {
									                ssize_t j = 0;
											            char *old_line = *line;
												                for (ssize_t i = 0; old_line[i]; i++)
															            {
																	                    char current = old_line[i];
																			                    char next = old_line[i + 1];
																					                    if (i != 0)
																								                    {
																											                        char previous = old_line[i - 1];
																														                    if (current == ';' || current == '&' || current == '|')
																																	                        {
																																					                        if ((current == ';' && next == ';') ||
																																										                            ((current == '&' || current == '|') && next == current))
																																									                        {
																																													                            new_line[j++] = ' ';
																																																                                new_line[j++] = current;
																																																				                            continue;
																																																							                            }
																																								                        else if ((previous == ';' && next != ' ') ||
																																													                                 (next != ' ' && previous == current))
																																												                        {
																																																                            new_line[j++] = current;
																																																			                                new_line[j++] = ' ';
																																																							                            continue;
																																																										                            }
																																											                        if (previous != ' ')
																																															                            new_line[j++] = ' ';
																																														                        new_line[j++] = current;
																																																	                        if (next != ' ')
																																																					                            new_line[j++] = ' ';
																																																				                        continue;
																																																							                    }
																																                    }
																							                    else if (current == ';')
																										                    {
																													                        if (i != 0 && old_line[i - 1] != ' ')
																																	                        new_line[j++] = ' ';
																																                    new_line[j++] = current;
																																		                        if (next != ' ' && next != ';')
																																						                        new_line[j++] = ' ';
																																					                    continue;
																																							                    }
																									                    new_line[j++] = current;
																											                }
														            new_line[j] = '\0';
															                free(*line);
																	            *line = new_line;
																		            }
						        }
}

/**
 *  * get_new_len - Calculate the new length of a line after processing.
 *   * @line: The line to check.
 *    *
 *     * Return: The new length of the line or -1 if an error occurs.
 *      *
 *       * Description: Truncates lines containing '#' comments with '\0'.
 *        */
ssize_t get_new_len(char *line)
{
	    ssize_t new_len = 0;
	        for (ssize_t i = 0; line[i]; i++)
			    {
				            char current = line[i];
					            char next = line[i + 1];
						            if (current == '#')
								            {
										                if (i == 0 || line[i - 1] == ' ')
													            {
															                    line[i] = '\0';
																	                    break;
																			                }
												        }
							            else if (i != 0)
									            {
											                if (current == ';' || current == '&' || current == '|')
														            {
																                    if (next == ';' || (next == current && line[i - 1] != ' '))
																			                        new_len++;
																		                    else if (next != ' ' && (next != current || line[i - 1] == current))
																					                        new_len++;
																				                }
													            else
															                    replace_logical_ops(&line[i], &new_len);
														            }
								            else if (current == ';')
										            {
												                if (i != 0 && line[i - 1] != ' ')
															                new_len++;
														            if (next != ' ' && next != ';')
																                    new_len++;
															            }
									            new_len++;
										        }
		    return new_len;
}

/**
 *  * replace_logical_ops - Checks a line for logical operators "||" or "&&".
 *   * @line: A pointer to the character to check in the line.
 *    * @new_len: Pointer to new_len in get_new_len function.
 *     */
void replace_logical_ops(char *line, ssize_t *new_len)
{
	    char previous = *(line - 1);
	        char current = *line;
		    char next = *(line + 1);

		        if (current == '&')
				    {
					            if (next == '&' && previous != ' ')
							                (*new_len)++;
						            else if (previous == '&' && next != ' ')
								                (*new_len)++;
							        }
			    else if (current == '|')
				        {
						        if (next == '|' && previous != ' ')
								            (*new_len)++;
							        else if (previous == '|' && next != ' ')
									            (*new_len)++;
								    }
}

