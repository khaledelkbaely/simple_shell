#include "shell.h"

/**
 * init - initialize the io_info struct
 *
 * @info: ...
 *
 * Return: always 1
 */

int init(io_info *info)
{
	info->prompt = "($) ";
	info->promptlen = _strlen(info->prompt);

	info->line = NULL;

	info->commands = malloc(sizeof(commands_t));
	info->commands->command = NULL;
	info->commands->next = NULL;
	build_path(&info->path, environ);
	/* TODO: buitlin build function */
	return (1);
}
/**
 * build_path - build path_t list
 *
 * @head: address of the first node in the list
 * @environ: environment varaibles where path is located
 *
 * Return: on success 0 else 1
 */
int build_path(path_t **head, char **environ)
{
	path_t *new, *ptr;
	int len_PATH_and_equal = _strlen("PATH=");
	int path_index = get_path_index(environ);
	char *tok;

	if (path_index == -1)
	{
		perror("get_path");
		return (0);
	}

	ptr = malloc(sizeof(path_t));
	if (ptr == NULL)
		return (1);
	*head = ptr;
	ptr->next = NULL;

	tok = strtok(environ[path_index] + len_PATH_and_equal, ":");
	ptr->dir = strdup(tok);

	while ((tok = strtok(NULL, ":")) != NULL)
	{
		new = malloc(sizeof(path_t));
		if (!new)
			return (1);

		new->next = NULL;
		new->dir = strdup(tok);

		ptr->next = new;
		ptr = ptr->next;
	}

	return (0);
}

/**
 * get_path_index - get the path index in the environment array
 *
 * @environ: envrioment array
 *
 * Return: the index of path
 */
int get_path_index(char **environ)
{
	char *path = "PATH";
	int i, j;
	int ispath = 0;

	i = 0;
	while (environ[i])
	{
		j = 0;
		while (path[j])
		{
			if (environ[i][j] != path[j])
				break;
			if (environ[i][j] == path[j])
				if (path[j + 1] == '\0')
				{
					ispath = 1;
					break;
				}
			j++;
		}
		if (ispath)
			break;
		i++;
	}
	if (ispath)
		return (i);
	return (-1);
}
