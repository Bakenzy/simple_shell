#include "shell.h"

void displayAllCommands(void);
void displayAliasHelp(void);
void displayCdHelp(void);
void displayExitHelp(void);
void displayHelpHelp(void);

/**
 *  * displayAllCommands - Displays information about all available shellby commands.
 *   */
void displayAllCommands(void)
{
	    char *message = "Shellby - Internal Shell Commands\n";
	        write(STDOUT_FILENO, message, _strlen(message));
		    message = "Type 'help' to see this list.\nType 'help [COMMAND]' to get ";
		        write(STDOUT_FILENO, message, _strlen(message));
			    message = "information about a specific command.\n\n";
			        write(STDOUT_FILENO, message, _strlen(message));

				    message = "  alias     - Handle aliases\n";
				        write(STDOUT_FILENO, message, _strlen(message));
					    message = "  cd        - Change the current directory\n";
					        write(STDOUT_FILENO, message, _strlen(message));
						    message = "  exit      - Exit the shell\n";
						        write(STDOUT_FILENO, message, _strlen(message));
							    message = "  env       - Display environment variables\n";
							        write(STDOUT_FILENO, message, _strlen(message));
								    message = "  setenv    - Set environment variables\n";
								        write(STDOUT_FILENO, message, _strlen(message));
									    message = "  unsetenv  - Unset environment variables\n";
									        write(STDOUT_FILENO, message, _strlen(message));
}

/**
 *  * displayAliasHelp - Displays information about the 'alias' command.
 *   */
void displayAliasHelp(void)
{
	    char *message = "alias: alias [NAME[='VALUE'] ...]\n";
	        write(STDOUT_FILENO, message, _strlen(message));
		    message = "\tHandles shell aliases.\n\n";
		        write(STDOUT_FILENO, message, _strlen(message));
			    message = "\talias - Print a list of all aliases in the format NAME='VALUE'.\n";
			        write(STDOUT_FILENO, message, _strlen(message));
				    message = "\talias name [name2 ...] - Print specific aliases.\n";
				        write(STDOUT_FILENO, message, _strlen(message));
					    message = "\talias NAME='VALUE' [...] - Define or update aliases.\n";
					        write(STDOUT_FILENO, message, _strlen(message));
}

/**
 *  * displayCdHelp - Displays information about the 'cd' command.
 *   */
void displayCdHelp(void)
{
	    char *message = "cd: cd [DIRECTORY]\n";
	        write(STDOUT_FILENO, message, _strlen(message));
		    message = "\tChange the current directory to DIRECTORY.\n\n";
		        write(STDOUT_FILENO, message, _strlen(message));
			    message = "\tIf no argument is given, cd is interpreted as 'cd $HOME'.\n";
			        write(STDOUT_FILENO, message, _strlen(message));
				    message = "\tIf the argument is '-', cd is interpreted as 'cd $OLDPWD'.\n";
				        write(STDOUT_FILENO, message, _strlen(message));
					    message = "\tEnvironment variables PWD and OLDPWD are updated after a directory change.\n";
					        write(STDOUT_FILENO, message, _strlen(message));
}

/**
 *  * displayExitHelp - Displays information about the 'exit' command.
 *   */
void displayExitHelp(void)
{
	    char *message = "exit: exit [STATUS]\n";
	        write(STDOUT_FILENO, message, _strlen(message));
		    message = "\tExit the shell.\n\n";
		        write(STDOUT_FILENO, message, _strlen(message));
			    message = "\tSTATUS is an integer used to exit the shell.\n";
			        write(STDOUT_FILENO, message, _strlen(message));
				    message = "\tIf no argument is given, exit is interpreted as 'exit 0'.\n";
				        write(STDOUT_FILENO, message, _strlen(message));
}

/**
 *  * displayHelpHelp - Displays information about the 'help' command.
 *   */
void displayHelpHelp(void)
{
	    char *message = "help: help\n";
	        write(STDOUT_FILENO, message, _strlen(message));
		    message = "\tDisplay information about available Shellby commands.\n\n";
		        write(STDOUT_FILENO, message, _strlen(message));
			    message = "\thelp [COMMAND]\n";
			        write(STDOUT_FILENO, message, _strlen(message));
				    message = "\tDisplay specific information about a command.\n";
				        write(STDOUT_FILENO, message, _strlen(message));
}
