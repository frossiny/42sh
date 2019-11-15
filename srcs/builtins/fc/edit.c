/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 06:38:23 by pcharrie          #+#    #+#             */
/*   Updated: 2019/11/15 21:37:57 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include "utils.h"
#include "shell.h"
#include "libft.h"
#include "variables.h"
#include "builtins.h"
#include "opt.h"

static int	fc_edit_write_file(t_fc_vars *fc)
{
	char	*path;
	int		i;
	int		fd;

	if (!(path = ft_strpathfile(getenv("HOME"), ".42sh_fc")))
		return (0);
	if ((fd = open(path, O_CREAT | O_WRONLY, 0777)) < 0)
	{
		ft_strdel(&path);
		return (0);
	}
	ft_strdel(&path);
	i = fc->tab_len - 1;
	while (i >= 0)
	{
		write(fd, fc->tab[i], ft_strlen(fc->tab[i]));
		write(fd, "\n", 1);
		i--;
	}
	close(fd);
	return (1);
}

int			fc_ed_args_resize(t_fc_vars *fc)
{
	char	**tab;
	char	*path;
	int		i;

	if (!(path = ft_strpathfile(getenv("HOME"), ".42sh_fc"))
		|| !(tab = ft_2dstrnew(ft_2dstrlen(fc->ed_args) + 1)))
	{
		ft_strdel(&path);
		return (0);
	}
	i = -1;
	while (fc->ed_args[++i])
	{
		if (!(tab[i] = ft_strdup(fc->ed_args[i])))
		{
			ft_strdel(&path);
			ft_2dstrdel(&tab);
			return (0);
		}
	}
	tab[i++] = path;
	tab[i++] = NULL;
	ft_2dstrdel(&fc->ed_args);
	fc->ed_args = tab;
	return (1);
}

int			fc_set_editor_path(t_fc_vars *fc)
{
	char *tmp;

	if ((tmp = get_exe_path(&g_shell, fc->ed_args[0])))
	{
		ft_strdel(&fc->ed_args[0]);
		fc->ed_args[0] = tmp;
		return (1);
	}
	return (0);
}

int			fc_set_editor(t_fc_vars *fc)
{
	if (!(fc->ed_args = ft_strsplit(fc->editor, ' '))
		|| !fc_ed_args_resize(fc))
		return (0);
	if (fc->ed_args[0][0] == '/' && access(fc->ed_args[0], F_OK))
	{
		ft_dprintf(2, "42sh: no such file or directory: %s", fc->ed_args[0]);
		return (0);
	}
	if (fc->ed_args[0][0] != '/' && !fc_set_editor_path(fc))
	{
		ft_dprintf(2, "42sh: command not found: %s", fc->ed_args[0]);
		return (0);
	}
	return (1);
}

void		fc_edit(t_fc_vars *fc)
{
	if (fc_set_editor(fc) && fc_edit_write_file(fc) && fc_edit_run_editor(fc))
		fc_exec_file();
	fc_edit_remove_file();
}
