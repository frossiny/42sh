/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 18:01:23 by pcharrie          #+#    #+#             */
/*   Updated: 2020/02/13 14:25:57 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include "get_next_line.h"

static int	write_line(char **line, char b[], int i, int j)
{
	char	*tmp;
	int		k;
	int		l;

	l = 0;
	while (*line && (*line)[l])
		l++;
	if (!(tmp = malloc(sizeof(char) * (l + j - i + 1))))
		return (0);
	k = 0;
	while (*line && (*line)[k])
	{
		tmp[k] = (*line)[k];
		k++;
	}
	while (i < j)
		tmp[k++] = b[i++];
	tmp[k] = '\0';
	if (*line)
		free(*line);
	*line = tmp;
	return (1);
}

int			get_next_line(int fd, char **line)
{
	static t_gnl g;

	(line ? *line = NULL : 0);
	while (line)
	{
		if ((g.c[fd] < 1 || g.i[fd] == BUFF_SIZE)
			|| (g.c[fd] < BUFF_SIZE && g.i[fd] == g.c[fd]))
		{
			if ((g.c[fd] = read(fd, g.b[fd], BUFF_SIZE)) < 1)
				return (*line == NULL ? g.c[fd] : 1);
			g.i[fd] = 0;
		}
		g.j = g.i[fd];
		while (g.b[fd][g.j] != '\n' && g.j < g.c[fd])
			g.j++;
		if (!write_line(line, g.b[fd], g.i[fd], g.j))
			return (-1);
		g.i[fd] = g.j;
		if (g.b[fd][g.j] == '\n' || (g.c[fd] < BUFF_SIZE && g.j == g.c[fd]))
		{
			(g.b[fd][g.j] == '\n' ? g.i[fd]++ : 0);
			return (1);
		}
	}
	return (-1);
}
