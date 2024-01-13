#include "shell.h"

/**
 * parse_line - parse line inputed into commands list
 *
 * @line: line to parse
 * @commands: command empty list
 *
 * Return: on success 1 else 0
 */

int parse_line(char *line, commands_t **commands)
{
	char *line_dup, *tok, **command = NULL;
	int cap = 2, i;

	if (line == NULL)
		return (0);
	line_dup = strdup(line);
	command = malloc(cap * sizeof(char *));
	if (command == NULL)
	{
		free(line_dup);
		return (0);
	}
	tok = strtok(line_dup, " \n");
	command[0] = strdup(tok);
	i = 1;
	while ((tok = strtok(NULL, " \n")) != NULL)
	{
		if (i >= cap)
		{
			cap *= 2;
			command = realloc(command, cap);
			if (command == NULL)
			{
				free(line_dup);
				perror("realloc");
				return (0);
			}
		}
		command[i++] = strdup(tok);
	}
	command[i] = NULL;
	if (add_command(command, commands))
	{
		free(line_dup);
		return (1);
	}
	return (0);
}

/**
 * add_command - add cmd to commands list
 *
 * @cmd: command to add
 * @commands: list to add cmd to
 *
 * Return: on success 1 else 0
 */

int add_command(char **cmd, commands_t **commands)
{
	commands_t *new;
	commands_t *ptr;

	ptr = *commands;
	if (!ptr->command && !ptr->next)
	{
		ptr->command = cmd;
		return (1);
	}

	new = malloc(sizeof(commands_t));
	if (new == NULL)
		return (0);

	new->command = cmd;
	new->next = NULL;

	while (ptr)
	{
		if (ptr->next == NULL)
		{
			ptr->next = new;
			break;
		}
		ptr = ptr->next;
	}
	return (1);
}

