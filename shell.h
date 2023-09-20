fndef _SHELL_H_
#define _SHELL_H_

#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#define END_OF_FILE -2
#define EXIT -3

extern char **environ;
extern char *name;
extern int hist;

typedef struct list_s
{
		char *dir;
			struct list_s *next;
} list_t;

typedef struct builtin_s
{
		char *name;
			int (*function)(char **argv, char **front);
} builtin_t;

typedef struct alias_s
{
		char *name;
			char *value;
				struct alias_s *next;
} alias_t;

alias_t *aliases;

ssize_t get_line(char **lineptr, size_t *n, FILE *stream);
void *reallocate(void *ptr, unsigned int old_size, unsigned int new_size);
char **tokenize_string(char *line, char *delimiters);
char *find_command_location(char *command);
list_t *parse_path_directories(char *path);
int execute_command(char **arguments, char **command_front);
void free_directory_list(list_t *head);
char *integer_to_string(int num);

void handle_input_line(char **line, ssize_t read);
void replace_variables(char **args, int *execution_result);
char *parse_arguments(char *line, int *execution_result);
int execute_arguments(char **args, char **front, int *execution_result);
int process_arguments(int *execution_result);
int validate_arguments(char **args);
void free_argument_list(char **args, char **front);
char **substitute_aliases(char **args);

int string_length(const char *s);
char *string_concatenate(char *dest, const char *src);
char *string_concatenate_n(char *dest, const char *src, size_t n);
char *string_copy(char *dest, const char *src);
char *string_find_character(char *s, char c);
int string_span(char *s, char *accept);
int string_compare(const char *s1, const char *s2);
int string_compare_n(const char *s1, const char *s2, size_t n);

int (*get_builtin_function(char *command))(char **args, char **front);
int shell_exit(char **args, char **front);
int shell_env(char **args, char **front);
int shell_setenv(char **args, char **front);
int shell_unsetenv(char **args, char **front);
int shell_cd(char **args, char **front);
int shell_alias(char **args, char **front);
int shell_help(char **args, char **front);

char **copy_environment(void);
void free_environment(void);
char **get_environment_variable(const char *variable);

int create_error_message(char **args, int error_code);
char *error_message_env(char **args);
char *error_message_1(char **args);
char *error_message_2_exit(char **args);
char *error_message_2_cd(char **args);
char *error_message_2_syntax(char **args);
char *error_message_126(char **args);
char *error_message_127(char **args);

alias_t *add_alias_to_end(alias_t **head, char *name, char *value);
void free_alias_list_memory(alias_t *head);
list_t *add_directory_to_end(list_t **head, char *directory);
void free_directory_list_memory(list_t *head);

void print_help_all(void);
void print_help_alias(void);
void print_help_cd(void);
void print_help_exit(void);
void print_help_help(void);
void print_help_env(void);
void print_help_setenv(void);
void print_help_unsetenv(void);
void print_help_history(void);

int process_file_commands(char *file_path, int *execution_result);

#endif /* _SHELL_H_ */
