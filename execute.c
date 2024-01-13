#include "shell.h"

/**
 * execute - execute command inputed
 *
 * @info: io_info type
 *
 * Return: Nothing
 */

void execute(io_info *info)
{
	commands_t *cmd_ptr;
	char *abs_path_name;
	pid_t id;

	cmd_ptr = info->commands;

	/* is buitin */
	if (info->line[0] == '.' && info->line[1] == '/')
		abs_path_name = strdup(cmd_ptr->command[0]);
	else
		abs_path_name = is_in_path(cmd_ptr->command[0], info->path);

	if (abs_path_name)
		id = fork();
	if (id == -1)
	{
		perror("fork");
		return;
	}

	if (id == 0)
	{
		cmd_ptr->command[0] = abs_path_name;
		execve(cmd_ptr->command[0], cmd_ptr->command, environ);
		perror("execve");
	}
	wait(NULL);
	free(abs_path_name);
	free(info->line);
	free_commands(&cmd_ptr);
	cmd_ptr = malloc(sizeof(commands_t));
	cmd_ptr->command = NULL;
	cmd_ptr->next = NULL;
	info->line = NULL;
}

/**
 * is_in_path - check if the command is in path directories
 *
 * @cmd: command to check in path
 * @path: list of the path directory to search for cmd in
 *
 * Return: absolute pathname of the file executable
 */

char *is_in_path(char *cmd, path_t *path)
{
	path_t *ptr;
	char *abs_path_name;

	ptr = path;

	abs_path_name = strdup(cmd);
	if (access(abs_path_name, F_OK | X_OK) == 0)
	{
		return (abs_path_name);
	}
	free(abs_path_name);
	while (ptr)
	{
		abs_path_name = get_abs_path_name(ptr->dir, cmd);
		if (abs_path_name == NULL)
		{
			ptr = ptr->next;
			free(abs_path_name);
			continue;
		}

		if (access(abs_path_name, F_OK | X_OK) == 0)
		{
			return (abs_path_name);
		}

		ptr = ptr->next;
		free(abs_path_name);
	}
	return (NULL);
}

/**
 * get_abs_path_name - get the absolute pathname of command
 *
 * @dir: directory name
 * @cmd: command executable
 *
 * Return: absolute pathname pointer if success
 *         else NULL
 */

char *get_abs_path_name(char *dir, char *cmd)
{
	int dir_len, cmd_len, i, j;
	char *abs;

	if (!dir || !cmd)
		return (NULL);

	dir_len = _strlen(dir);
	cmd_len = _strlen(cmd);

	abs = malloc((dir_len + cmd_len + 2) * sizeof(char));
	if (abs == NULL)
		return (NULL);

	i = 0;
	while (dir[i])
	{
		abs[i] = dir[i];
		i++;
	}
	abs[i++] = '/';
	j = 0;
	while (cmd[j])
	{
		abs[i + j] = cmd[j];
		j++;
	}
	abs[i + j] = '\0';

	return (abs);
}

