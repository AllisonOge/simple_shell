#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/**
 * _getline - reads an entire line from file descriptor
 * @lineptr: pointer to the buffer containing the read line
 * @n: size of the buffer
 * @fd: file descriptor to read from
 *
 * Return: number of bytes read, -1 on failure and -2 on end of file
 *
 * Description: this function reads an entire line from stream, storing the
 * address of the buffer containing the text into ptr. The buffer is null-
 * terminated and includes the newline character, if one was found.
 */
ssize_t _getline(char **lineptr, size_t *n, int fd)
{
	static char buffer[BUFF_SIZE], *ptr;
	static int nread;
	char *tmp = 0;
	size_t buffer_pos = 0;

	if (fd < 0 || !lineptr || !n)
		return (-1);
	/* allocate memory if pointer is NULL */
	if (!*lineptr)
	{
		*lineptr = malloc(BUFF_SIZE);
		if (!*lineptr)
			return (-1);
		*n = BUFF_SIZE;
	}
	/* read from file descriptor if buffer is empty */
	if (ptr == NULL || nread == 0)
	{
		nread = read(fd, buffer, BUFF_SIZE);
		ptr = buffer;
	}
	if (nread == -1)
		return (-1);
	if (nread == 0)
		return (-2);
	/* read line */
	while (*ptr != '\n')
	{
		/* reallocate memory if buffer is full */
		if (buffer_pos + 1 >= *n)
		{
			tmp = realloc(ptr, *n + BUFF_SIZE);
			if (!tmp)
				return (-1);
			ptr = tmp;
			*n += BUFF_SIZE;
		}
		(*lineptr)[buffer_pos++] = *ptr++; /* store character in buffer */
		nread--;
		/* read more characters if buffer is empty */
		if (nread == 0)
		{
			nread = read(fd, buffer, BUFF_SIZE);
			ptr = buffer;
			if (nread == -1)
				return (-1);
			if (nread == 0)
				break;
		}
	}
	/* terminate line with new-line and null-character */
	(*lineptr)[buffer_pos++] = '\n';
	(*lineptr)[buffer_pos] = '\0';
	ptr++;
	nread--;
	return (buffer_pos);
}

/**
 * _strtok - splits a string into tokens
 * @str: string to split
 * @delim: delimiter character
 *
 * Return: pointer to the next token, NULL if no more tokens are available
*/
char *_strtok(char *str, const char *delim)
{
	static char *next;
	char *tok;

	/* if str is NULL, use saved pointer as start of string */
	if (str == NULL)
		str = next;

	/* if no more tokens are available, return NULL */
	if (*str == '\0')
	{
		next = str;
		return (NULL);
	}
	str += strspn(str, delim); /* skip to the end of the token */
	tok = str;
	str += strcspn(str, delim); /* find end of token */
	/*
	 * if end of string is reached, set next to the end of the string,
	 * else null-terminate delimiter and set next to the next token
	 */
	if (*str == '\0')
		next = str;
	else
	{
		*str = '\0';
		next = str + 1;
	}
	return (tok);
}
