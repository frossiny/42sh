/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 21:37:37 by pcharrie          #+#    #+#             */
/*   Updated: 2019/11/15 21:38:34 by pcharrie         ###   ########.fr       */
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

int		fc_edit_run_editor(t_fc_vars *fc)
{
	int		pid;

	if (access(fc->ed_args[0], F_OK))
		return (0);
	if (!(pid = fork()))
	{
		unregister_signals();
		g_shell.able_termcaps ? restore_shell(g_shell.prev_term) : 0;
		execve(fc->ed_args[0], fc->ed_args, NULL);
	}
	waitpid(pid, NULL, 0);
	g_shell.able_termcaps ? termcaps_init(NULL) : 0;
	return (pid != -1);
}

void	fc_edit_remove_file(void)
{
	char *path;

	if (!(path = ft_strpathfile(getenv("HOME"), ".42sh_fc")))
		return ;
	unlink(path);
	ft_strdel(&path);
}
