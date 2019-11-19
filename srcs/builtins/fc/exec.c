/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 06:37:24 by pcharrie          #+#    #+#             */
/*   Updated: 2019/11/19 04:37:37 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include "utils.h"
#include "shell.h"
#include "libft.h"
#include "variables.h"
#include "builtins.h"
#include "opt.h"
#include "get_next_line.h"

char	**g_fc_tab = NULL;

int		fc_get_mode(t_fc_vars *fc)
{
	if (fc->exec)
		return (1);
	if (fc->list)
		return (2);
	return (3);
}

void	fc_exec_tab(t_fc_vars *fc)
{
	int i;

	if (!fc->tab || !(g_fc_tab = ft_2dstrnew(fc->tab_len)))
		return ;
	i = 0;
	while (fc->tab[i])
	{
		if (!(g_fc_tab[i] = ft_strdup(fc->tab[i])))
			return (ft_2dstrdel(&g_fc_tab));
		i++;
	}
}

int		fc_get_file_len(void)
{
	char	*path;
	int		fd;
	char	*line;
	int		i;

	if (!(path = ft_strpathfile(getenv("HOME"), ".42sh_fc"))
		|| (fd = open(path, O_RDONLY)) < 0)
	{
		ft_strdel(&path);
		return (-1);
	}
	ft_strdel(&path);
	i = 0;
	while (get_next_line(fd, &line) > 0)
	{
		i++;
		ft_strdel(&line);
	}
	close(fd);
	return (i);
}

void	fc_exec_file(void)
{
	char	*path;
	int		fd;
	char	*line;
	int		len;

	if ((len = fc_get_file_len()) < 0
		|| !(g_fc_tab = ft_2dstrnew(len))
		|| !(path = ft_strpathfile(getenv("HOME"), ".42sh_fc")))
		return (ft_2dstrdel(&g_fc_tab));
	if ((fd = open(path, O_RDONLY)) < 0)
	{
		ft_2dstrdel(&g_fc_tab);
		return (ft_strdel(&path));
	}
	ft_strdel(&path);
	len = 0;
	while (get_next_line(fd, &line) > 0)
		g_fc_tab[len++] = line;
	close(fd);
}
