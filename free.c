#include "shell.h"

/**
 * free_all - free all memory allocated
 *
 * @info: io_info allocated
 *
 * Return: Nothing
 */

void free_all(io_info *info)
{
	free(info->line);

	free_path(&info->path);
}

/**
 * free_commands - free list commands_t
 *
 * @commands: list to free
 *
 * Return: Nothing
 */
void free_commands(commands_t **commands)
{
	int i;
	commands_t *ptr;

	ptr = *commands;
	if (!ptr->command && !ptr->next)
	{
		free(ptr);
		return;
	}

	while (ptr)
	{
		i = 0;
		while (ptr->command[i])
		{
			free(ptr->command[i++]);
		}
		free(ptr->command);

		ptr = ptr->next;

		free(*commands);
		*commands = ptr;
	}
}

/**
 * free_path - free list path_t
 *
 * @path: list to free
 *
 * Return: Nothing
 */

void free_path(path_t **path)
{
	path_t *ptr;

	ptr = *path;
	while (ptr)
	{
		free(ptr->dir);

		*path = ptr->next;

		free(ptr);

		ptr = *path;
	}
}

