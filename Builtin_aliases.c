#include "shell.h"

int executeAliasCommand(char **args, char __attribute__((__unused__)) * *front);
void setAlias(char *aliasName, char *aliasValue);
void printAliases(alias_t *aliasesList);

/**
 *  * executeAliasCommand - Builtin command to handle aliases - prints all aliases,
 *   * specific aliases, or sets an alias.
 *    * @args: Array of arguments.
 *     * @front: Double pointer to the beginning of args.
 *      *
 *       * Return: -1 on error, 0 otherwise.
 *        */
int executeAliasCommand(char **args, char __attribute__((__unused__)) * *front)
{
	    alias_t *currentAlias = aliases;
	        int i, returnValue = 0;
		    char *value;

		        if (!args[0])
				    {
					            while (currentAlias)
							            {
									                printAliases(currentAlias);
											            currentAlias = currentAlias->next;
												            }
						            return (returnValue);
							        }
			    for (i = 0; args[i]; i++)
				        {
						        currentAlias = aliases;
							        value = _strchr(args[i], '=');
								        if (!value)
										        {
												            while (currentAlias)
														                {
																	                if (_strcmp(args[i], currentAlias->name) == 0)
																				                {
																							                    printAliases(currentAlias);
																									                        break;
																												                }
																			                currentAlias = currentAlias->next;
																					            }
													                if (!currentAlias)
																                returnValue = createError(args + i, 1);
															        }
									        else
											            setAlias(args[i], value);
										    }
			        return (returnValue);
}

/**
 *  * setAlias - Set an alias with a new value or create a new alias.
 *   * @aliasName: Name of the alias.
 *    * @value: Value of the alias (with '=').
 *     */
void setAlias(char *aliasName, char *value)
{
	    alias_t *currentAlias = aliases;
	        int length, j, k;
		    char *newValue;

		        *value = '\0';
			    value++;
			        length = _strlen(value) - _strspn(value, "'\"");
				    newValue = malloc(sizeof(char) * (length + 1));
				        if (!newValue)
						        return;
					    for (j = 0, k = 0; value[j]; j++)
						        {
								        if (value[j] != '\'' && value[j] != '"')
										            newValue[k++] = value[j];
									    }
					        newValue[k] = '\0';
						    while (currentAlias)
							        {
									        if (_strcmp(aliasName, currentAlias->name) == 0)
											        {
													            free(currentAlias->value);
														                currentAlias->value = newValue;
																            break;
																	            }
										        currentAlias = currentAlias->next;
											    }
						        if (!currentAlias)
								        addAliasEnd(&aliases, aliasName, newValue);
}

/**
 *  * printAliases - Print an alias in the format: name='value'.
 *   * @alias: Pointer to an alias.
 *    */
void printAliases(alias_t *alias)
{
	    char *aliasString;
	        int length = _strlen(alias->name) + _strlen(alias->value) + 4;

		    aliasString = malloc(sizeof(char) * (length + 1));
		        if (!aliasString)
				        return;
			    _strcpy(aliasString, alias->name);
			        _strcat(aliasString, "='");
				    _strcat(aliasString, alias->value);
				        _strcat(aliasString, "'\n");

					    write(STDOUT_FILENO, aliasString, length);
					        free(aliasString);
}

/**
 *  * replaceAliases - Replace matching aliases in the arguments with their values.
 *   * @args: Pointer to an array of arguments.
 *    *
 *     * Return: Pointer to the modified arguments.
 *      */
char **replaceAliases(char **args)
{
	    alias_t *currentAlias;
	        int i;
		    char *newValue;

		        if (_strcmp(args[0], "alias") == 0)
				        return (args);
			    for (i = 0; args[i]; i++)
				        {
						        currentAlias = aliases;
							        while (currentAlias)
									        {
											            if (_strcmp(args[i], currentAlias->name) == 0)
													                {
																                newValue = malloc(sizeof(char) * (_strlen(currentAlias->value) + 1));
																		                if (!newValue)
																					                {
																								                    freeArgs(args, args);
																										                        return (NULL);
																													                }
																				                _strcpy(newValue, currentAlias->value);
																						                free(args[i]);
																								                args[i] = newValue;
																										                i--;
																												                break;
																														            }
												                currentAlias = currentAlias->next;
														        }
								    }
			        return (args);
}
