#include "shell.h"

int calculateDigitLength(int num);
char *convertIntToString(int num);
int handleError(char **args, int err);

/**
 *  * calculateDigitLength - Calculates the length of digits in a number.
 *   * @num: The number to measure.
 *    *
 *     * Return: The digit length.
 *      */
int calculateDigitLength(int num)
{
	    unsigned int num1;
	        int len = 1;

		    if (num < 0)
			        {
					        len++;
						        num1 = num * -1;
							    }
		        else
				    {
					            num1 = num;
						        }

			    while (num1 > 9)
				        {
						        len++;
							        num1 /= 10;
								    }

			        return len;
}

/**
 *  * convertIntToString - Converts an integer to a string.
 *   * @num: The integer.
 *    *
 *     * Return: The converted string.
 *      */
char *convertIntToString(int num)
{
	    char *buffer;
	        int len = calculateDigitLength(num);
		    unsigned int num1;

		        buffer = malloc(sizeof(char) * (len + 1));
			    if (!buffer)
				            return NULL;

			        buffer[len] = '\0';

				    if (num < 0)
					        {
							        num1 = num * -1;
								        buffer[0] = '-';
									    }
				        else
						    {
							            num1 = num;
								        }

					    len--;

					        do
							    {
								            buffer[len] = (num1 % 10) + '0';
									            num1 /= 10;
										            len--;
											        } while (num1 > 0);

						    return buffer;
}

/**
 *  * handleError - Writes a custom error message to stderr.
 *   * @args: An array of arguments.
 *    * @err: The error value.
 *     *
 *      * Return: The error value.
 *       */
int handleError(char **args, int err)
{
	    char *error;

	        switch (err)
			    {
				        case -1:
						        error = generateEnvironmentError(args);
							        break;
								    case 1:
								        error = generateError1(args);
									        break;
										    case 2:
										        if (*args[0] == 'e')
												            error = generateError2Exit(++args);
											        else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
													            error = generateSyntaxError(args);
												        else
														            error = generateError2Cd(args);
													        break;
														    case 126:
														        error = generatePermissionDeniedError(args);
															        break;
																    case 127:
																        error = generateCommandNotFoundError(args);
																	        break;
																		    }

		    write(STDERR_FILENO, error, _strlen(error));

		        if (error)
				        free(error);

			    return err;
}
