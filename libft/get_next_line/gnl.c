/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gnl.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/24 09:55:37 by bmans          #+#    #+#                */
/*   Updated: 2020/03/05 14:53:44 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

static char	prepare_line(char **tline)
{
	*tline = malloc(sizeof(char));
	if (!tline || !(*tline))
		return (0);
	**tline = '\0';
	return (1);
}

static void	copy_str(char *dst, char *src, int start, int end)
{
	int i;

	i = 0;
	while (start < end)
	{
		dst[i] = src[start];
		i++;
		start++;
	}
}

static char	append(char **tline, int *index, int *cread, char *buf)
{
	char	*newline;
	int		newindex;
	int		oldlen;

	newindex = index;
	while (newindex < BUFFER_SIZE && buf[newindex] && buf[newindex] != '\n')
		newindex++;
	oldlen = 0;
	while ((*tline)[oldlen])
		oldlen++;
	newline = malloc(sizeof(char) * (oldlen + newindex - *index + 1));
	if (!newline)
		return (0);
	copy_str(newline, *tline, 0, oldlen);
	copy_str(newline + oldlen, buf, *index, newindex);
	newline[oldlen + newindex - *index] = '\0';
	free(*tline);
	*tline = newline;
	*cread -= newindex - *index;
	*index = newindex;
	if (*index == BUFFER_SIZE)
		*index = 0;
	return (1);
}

static char	read_buf(char *buf, int fd, int *cread, int *index)
{
	int i;

	if (buf[*index] == '\n')
	{
		(*index) = ((*index) + 1) % BUFFER_SIZE;
		(*cread)--;
	}
	if (!buf[*index])
		*index = 0;
	if (*cread == 0)
	{
		i = 0;
		while (i < BUFFER_SIZE)
		{
			buf[i] = '\0';
			i++;
		}
		*cread = read(fd, buf, BUFFER_SIZE);
		if (cread <= 0)
			return (0);
	}
	return (1);
}

int			get_next_line(int fd, char **line)
{
	static char	buf[BUFFER_SIZE];
	static int	index = 0;
	static int	cread = 0;
	char		*tline;

	if (fd < 0 || read(0, buf, 0) || !prepare_line(&tline))
		return (-1);
	while (read_buf(buf, fd, &cread, &index))
	{
		if (!append(&tline, &index, &cread, buf))
			return (-1);
		if (!buf[index] || buf[index] == '\n')
			break ;
	}
	*line = tline;
	return (cread > 0 ? 1 : cread);
}
