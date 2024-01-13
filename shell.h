#ifndef _SHELL_H
#define _SHELL_H

#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/signal.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define SIZE_OF_BUFFER 1024
#define FLUSH_BUFFER -1


extern char **environ;

/**
 * struct commands - list of 2D array of strings
 *
 * @command: 2D array of strings NULL terminated
 * @next: next node in the list
 */
typedef struct commands
{
	char **command;
	struct commands *next;
} commands_t;

/**
 * struct path_t - list of strings of the path env variable
 *
 * @dir: executable dir
 * @next: next node in the list
 */
typedef struct path_t
{
	char *dir;
	struct path_t *next;
} path_t;

/**
 * struct builtin - built-in functions
 *
 * @name: name of the builtin
 * @next: next node in the list
 */
typedef struct builtin
{
	char *name;
	/* TODO: funtion pointer for builtins */
	struct builtin *next;
} builtin_t;

/**
 * struct io_info - input output information
 *
 * @prompt: prompt to print before taking input
 * @promptlen: length of the prompt
 * @fd: file descriptor to read from
 * @line: line inputed
 * @commands: list of 2D NULL terminated array of strings
 * @path: list of the path directories
 * @builtins: list of builtin funtions
 *
 */
typedef struct io_info
{
	char *prompt;
	int promptlen;
	int fd;
	char *line;
	commands_t *commands;
	path_t *path;
	builtin_t *builtins;
} io_info;

/* strings.c */
int _strlen(char *str);
int _strcmp(char *str1, char *str2);
char *start_with(char *str1, char *str2);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
char *_strdup(char *str);
void _puts(char *str);
int _putchar(char c);

int init(io_info *info);

int get_path_index(char **environ);
int build_path(path_t **head, char **environ);

int get_input(char **lineptr, size_t *size, int ac);

int parse_line(char *line, commands_t **commands);
int add_command(char **cmd, commands_t **commands);

void free_all(io_info *info);
void free_commands(commands_t **commands);
void free_path(path_t **path);

void execute(io_info *info);
char *is_in_path(char *cmd, path_t *path);
char *get_abs_path_name(char *dir, char *cmd);
#endif
