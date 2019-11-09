/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 15:41:21 by pcharrie          #+#    #+#             */
/*   Updated: 2019/11/07 18:13:23 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

static int	ft_strredupmem(char **s1, char *s2)
{
	if (!s1 || !s2)
		return (0);
	ft_strdel(s1);
	*s1 = s2;
	return (1);
}

static char	*cd_2dstrtopath(char **tab, int size)
{
	char	*path;
	int		i;
	int		j;
	int		k;

	i = -1;
	j = 0;
	while (++i < size)
		if (tab[i])
			j += ft_strlen(tab[i]) + 1;
	if (!(path = ft_strnew(j)))
		return (NULL);
	i = -1;
	k = 0;
	while (++i < size)
	{
		if (tab[i])
		{
			j = 0;
			path[k++] = '/';
			while (tab[i][j])
				path[k++] = tab[i][j++];
		}
	}
	return (path);
}

static void	cd_buildpath_set2dstr(char **tab, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		if (ft_strequ(tab[i], "."))
			ft_strdel(&tab[i]);
		else if (ft_strequ(tab[i], ".."))
		{
			ft_strdel(&tab[i--]);
			while (i >= 0)
			{
				if (tab[i])
				{
					ft_strdel(&tab[i]);
					break ;
				}
				i--;
			}
		}
		i++;
	}
}

char		*cd_buildpath(char *path)
{
	char	**tab;
	int		size;
	char	*built_path;

	if ((path[0] != '/'
		&& !(ft_strredupmem(&path, ft_strjoint(g_pwd, "/", path))))
		|| !(tab = ft_strsplit(path, '/')))
		return (NULL);
	ft_strdel(&path);
	size = ft_2dstrlen(tab);
	cd_buildpath_set2dstr(tab, size);
	built_path = cd_2dstrtopath(tab, size);
	ft_2dstrndel(&tab, size);
	return (built_path);
}
