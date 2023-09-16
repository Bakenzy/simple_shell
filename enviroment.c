#include "shell.h"

char **duplicateEnvironment(void);
void releaseEnvironment(char **env);
char **findEnvironmentVariable(const char *variable);

/**
 *  * duplicateEnvironment - Creates a copy of the environment.
 *   *
 *    * Return: If an error occurs - NULL.
 *     *         Otherwise - a double pointer to the new copy.
 *      */
char **duplicateEnvironment(void)
{
	    char **newEnvironment;
	        size_t size;
		    int index;

		        for (size = 0; environ[size]; size++)
				        ;

			    newEnvironment = malloc(sizeof(char *) * (size + 1));
			        if (!newEnvironment)
					        return (NULL);

				    for (index = 0; environ[index]; index++)
					        {
							        newEnvironment[index] = malloc(_strlen(environ[index]) + 1);

								        if (!newEnvironment[index])
										        {
												            for (index--; index >= 0; index--)
														                    free(newEnvironment[index]);
													                free(newEnvironment);
															            return (NULL);
																            }
									        _strcpy(newEnvironment[index], environ[index]);
										    }
				        newEnvironment[index] = NULL;

					    return newEnvironment;
}

/**
 *  * releaseEnvironment - Frees the memory used by the environment copy.
 *   */
void releaseEnvironment(char **env)
{
	    int index;

	        for (index = 0; env[index]; index++)
			        free(env[index]);
		    free(env);
}

/**
 *  * findEnvironmentVariable - Retrieves an environmental variable from the environment.
 *   * @variable: The name of the environmental variable to retrieve.
 *    *
 *     * Return: If the environmental variable does not exist - NULL.
 *      *         Otherwise - a pointer to the environmental variable.
 *       */
char **findEnvironmentVariable(const char *variable)
{
	    int index, length;

	        length = _strlen(variable);
		    for (index = 0; environ[index]; index++)
			        {
					        if (_strncmp(variable, environ[index], length) == 0)
							            return (&environ[index]);
						    }

		        return NULL;
}
