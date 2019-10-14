/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 13:44:42 by frossiny          #+#    #+#             */
/*   Updated: 2019/05/01 15:10:37 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char			*ft_line(char *s, char c)
{
	int			i;
	char		*new;

	i = 0;
	while (s[i] != c)
		i++;
	if (!(new = (char *)malloc(sizeof(char) * i + 1)))
		return (NULL);
	i = 0;
	while (s[i] != c)
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

int				ft_ret(char **line, char **tmp, int new)
{
	char		*old;

	if (new == 0 && ft_strlen(*tmp) == 0)
	{
		*line = NULL;
		return (0);
	}
	if (ft_strchr(*tmp, '\n') != NULL)
	{
		old = *tmp;
		*line = ft_line(*tmp, '\n');
		*tmp = ft_strdup(ft_strchr(*tmp, '\n') + 1);
		if (ft_strlen(*tmp) == 0)
			ft_strdel(tmp);
		free(old);
	}
	else
	{
		*line = ft_strdup(*tmp);
		ft_strclr(*tmp);
	}
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	static char	*tmp[OPEN_MAX + 1];
	char		*old;
	char		buff[BUFF_SIZE + 1];
	int			new;

	while ((new = read(fd, buff, BUFF_SIZE)))
	{
		if (new == -1)
			return (-1);
		buff[new] = '\0';
		if (tmp[fd] == NULL)
			tmp[fd] = ft_strdup(buff);
		else
		{
			old = tmp[fd];
			tmp[fd] = ft_strjoin(tmp[fd], buff);
			free(old);
		}
		if (ft_strchr(buff, '\n') != NULL)
			break ;
	}
	return (ft_ret(line, &tmp[fd], new));
}
