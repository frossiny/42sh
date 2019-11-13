/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 06:38:23 by pcharrie          #+#    #+#             */
/*   Updated: 2019/11/13 17:24:00 by pcharrie         ###   ########.fr       */
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
	i = -1;
	while (fc->tab[++i])
	{
		write(fd, fc->tab[i], ft_strlen(fc->tab[i]));
		write(fd, "\n", 1);
	}
	close(fd);
	return (1);
}

static int	fc_edit_run_editor(t_fc_vars *fc)
{
	int		pid;
	char	*args[3];
	char	*path;

	if (access(fc->editor, F_OK | X_OK)
		|| !(path = ft_strpathfile(getenv("HOME"), ".42sh_fc")))
		return (0);
	if (!(pid = fork()))
	{
		args[0] = fc->editor;
		args[1] = path;
		args[2] = NULL;
		execve(fc->editor, args, NULL);
	}
	else if (pid > 0)
	{
		waitpid(pid, NULL, 0);
		ft_strdel(&path);
	}
	else
	{
		ft_strdel(&path);
		return (0);
	}
	return (1);
}

static void	fc_edit_remove_file(void)
{
	char *path;

	if (!(path = ft_strpathfile(getenv("HOME"), ".42sh_fc")))
		return ;
	unlink(path);
	ft_strdel(&path);
}

int			fc_set_editor_path(t_fc_vars *fc)
{
	char *tmp;

	if ((tmp = get_exe_path(&g_shell, fc->editor)))
	{
		ft_strdel(&fc->editor);
		fc->editor = tmp;
		return (1);
	}
	return (0);
}

int			fc_set_editor(t_fc_vars *fc)
{
	
	if (fc->editor[0] == '/' && access(fc->editor, F_OK))
	{
		ft_dprintf(2, "42sh: no such file or directory: %s", fc->editor);
		return (0);
	}
	if (fc->editor[0] != '/' && !fc_set_editor_path(fc))
	{
		ft_dprintf(2, "42sh: command not found: %s", fc->editor);
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
