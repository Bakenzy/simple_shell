#include "shell.h"

int token_length(char *str, char *delimiter);
int count_tokens(char *str, char *delimiter);
char **custom_strtok(char *line, char *delimiter);

/**
 *  * token_length - Finds the length of the token delimited by a character.
 *   * @str: The string to search within.
 *    * @delimiter: The delimiter character.
 *     *
 *      * Return: The length of the token.
 *       */
int token_length(char *str, char *delimiter)
{
		int length = 0;

			while (*str && *str != *delimiter)
					{
								length++;
										str++;
											}

				return (length); /* Added parentheses for return value */
}

/**
 *  * count_tokens - Counts the number of tokens delimited by a character.
 *   * @str: The string to search within.
 *    * @delimiter: The delimiter character.
 *     *
 *      * Return: The number of tokens.
 *       */
int count_tokens(char *str, char *delimiter)
{
		int tokens = 0;

			while (*str)
					{
								if (*str != *delimiter)
											{
															tokens++;
																		str += token_length(str, delimiter);
																				}
										else
													{
																	str++;
																			}
											}

				return (tokens); /* Added parentheses for return value */
}

/**
 *  * custom_strtok - Tokenizes a string based on a delimiter character.
 *   * @line: The string to tokenize.
 *    * @delimiter: The delimiter character.
 *     *
 *      * Return: An array of tokens.
 *       */
char **custom_strtok(char *line, char *delimiter)
{
		char **tokens;
			int index = 0, num_tokens, token_length, i, j;

				num_tokens = count_tokens(line, delimiter);

					if (num_tokens == 0)
								return (NULL); /* Added parentheses for return value */

						tokens = malloc(sizeof(char *) * (num_tokens + 1));

							if (!tokens)
										return (NULL); /* Added parentheses for return value */

								for (i = 0; i < num_tokens; i++)
										{
													while (*line == *delimiter)
																	line++;

															token_length = token_length(line, delimiter);
																	tokens[i] = malloc(sizeof(char) * (token_length + 1));

																			if (!tokens[i])
																						{
																										for (j = 0; j < i; j++)
																															free(tokens[j]);
																													free(tokens);
																																return (NULL); /* Added parentheses for return value */
																																		}

																					for (j = 0; j < token_length; j++)
																								{
																												tokens[i][j] = line[j];
																														}
																							tokens[i][j] = '\0';

																									line += token_length;
																										}

									tokens[num_tokens] = NULL;
										return (tokens); /* Added parentheses for return value */
}
