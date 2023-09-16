#include "shell.h"

char *modifyPath(char *path);
list_t *tokenizePath(char *path);

/**
 *  * locateCommand - Locates a command in the PATH.
 *   * @command: The command to locate.
 *    *
 *     * Return: If an error occurs or the command cannot be located - NULL.
 *      *         Otherwise - the full pathname of the command.
 *       */
char *locateCommand(char *command) {
	    char **path, *temp;
	        list_t *dirs, *head;
		    struct stat st;

		        path = getenv("PATH");
			    if (!path || !(*path))
				            return (NULL);

			        dirs = tokenizePath(*path + 5);
				    head = dirs;

				        while (dirs) {
						        temp = malloc(strlen(dirs->dir) + strlen(command) + 2);
							        if (!temp)
									            return (NULL);

								        strcpy(temp, dirs->dir);
									        strcat(temp, "/");
										        strcat(temp, command);

											        if (stat(temp, &st) == 0) {
													            free_list(head);
														                return (temp);
																        }

												        dirs = dirs->next;
													        free(temp);
														    }

					    free_list(head);

					        return (NULL);
}

/**
 *  * modifyPath - Modify the PATH variable to handle leading/sandwiched/trailing colons.
 *   * @path: The colon-separated list of directories.
 *    *
 *     * Return: A modified copy of path with any leading/sandwiched/trailing colons replaced
 *      *         with the current working directory.
 *       */
char *modifyPath(char *path) {
	    int i, length = 0;
	        char *path_copy, *pwd;

		    pwd = getenv("PWD") + 4;
		        for (i = 0; path[i]; i++) {
				        if (path[i] == ':') {
						            if (path[i + 1] == ':' || i == 0 || path[i + 1] == '\0')
								                    length += strlen(pwd) + 1;
							                else
										                length++;
									        } else {
											            length++;
												            }
					    }

			    path_copy = malloc(sizeof(char) * (length + 1));
			        if (!path_copy)
					        return (NULL);

				    path_copy[0] = '\0';
				        for (i = 0; path[i]; i++) {
						        if (path[i] == ':') {
								            if (i == 0) {
										                    strcat(path_copy, pwd);
												                    strcat(path_copy, ":");
														                } else if (path[i + 1] == ':' || path[i + 1] == '\0') {
																	                strcat(path_copy, ":");
																			                strcat(path_copy, pwd);
																					            } else {
																							                    strcat(path_copy, ":");
																									                }
									            } else {
											                strncat(path_copy, &path[i], 1);
													        }
							    }

					    return (path_copy);
}

/**
 *  * tokenizePath - Tokenize a colon-separated list of directories into a linked list.
 *   * @path: The colon-separated list of directories.
 *    *
 *     * Return: A pointer to the initialized linked list.
 *      */
list_t *tokenizePath(char *path) {
	    int index;
	        char **dirs, *path_copy;
		    list_t *head = NULL;

		        path_copy = modifyPath(path);
			    if (!path_copy)
				            return (NULL);

			        dirs = _strtok(path_copy, ":");
				    free(path_copy);

				        if (!dirs)
						        return (NULL);

					    for (index = 0; dirs[index]; index++) {
						            if (add_node_end(&head, dirs[index]) == NULL) {
								                free_list(head);
										            free(dirs);
											                return (NULL);
													        }
							        }

					        free(dirs);

						    return (head);
}
