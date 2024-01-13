#include "shell.h"

/**
 * get_input - get line input with getline func
 *
 * @lineptr: address to store the line inputed
 * @size: address of the size of char array line
 * @ac: number of arguments passed to the program
 *
 * Return: number of chars read
 */

int get_input(char **lineptr, size_t *size, int ac)
{
	int chars_read;

	*size = 0;
	if (isatty(STDIN_FILENO) || ac == 1)
		chars_read = getline(lineptr, size, stdin);

	return (chars_read);
}

