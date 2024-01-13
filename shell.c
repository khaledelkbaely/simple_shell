#include "shell.h"

/**
 * main - entry point for the shell program
 *
 * @ac: number of arguments passed in
 * @av: string array of the arguments
 *
 * Return: on success always 0
 */
int main(int ac, char **av)
{
	io_info info;
	size_t size = 0;

	init(&info);
	if (isatty(STDIN_FILENO) && ac == 2)
		info.fd = open(av[1], O_RDONLY);
	else
		info.fd = STDOUT_FILENO;

	while (1)
	{
		if (isatty(STDIN_FILENO) && ac == 1)
			write(info.fd, info.prompt, info.promptlen);

		if (get_input(&info.line, &size, ac) == EOF)
		{
			free_all(&info);
			break;
		}

		if (info.line[0] == '\n')
		{
			free(info.line);
			continue;
		}
		if (parse_line(info.line, &info.commands) == 0)
		{
			free(info.line);
			continue;
		}


		execute(&info);
	}
	return (0);
}

int _strlen(char *str)
{
	char *s = str;

	while (*str++)
		;

	return (str - s);
}
