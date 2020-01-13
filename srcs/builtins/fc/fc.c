/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 17:13:15 by pcharrie          #+#    #+#             */
/*   Updated: 2020/01/13 17:05:40 by lubenard         ###   ########.fr       */
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

void	fc_vars_init(t_fc_vars *fc)
{
	fc->from = g_shell.history.size - 1 - 15;
	fc->to = g_shell.history.size - 1;
	fc->from_a = 0;
	fc->to_a = 0;
	fc->list = 0;
	fc->exec = 0;
	fc->rm = 0;
	fc->rv = 0;
	fc->editor = NULL;
	fc->ed_args = NULL;
	fc->s_cmd = NULL;
	fc->i = 0;
	fc->tab_len = 0;
	fc->tab = NULL;
}

void	fc_proceed(t_fc_vars *fc)
{
	if (fc->exec)
	{
		if (fc->s_cmd)
			fc_set_exec_cmd(fc);
		fc_exec_tab(fc);
	}
	else if (fc->list)
		fc_list(fc);
	else
	{
		if (!fc->editor && !(fc->editor = ft_strdup("/bin/ed")))
			return ;
		fc_edit(fc);
	}
}

void	fc_vars_del(t_fc_vars *fc)
{
	ft_2dstrdel(&fc->tab);
	ft_2dstrdel(&fc->ed_args);
	ft_strdel(&fc->editor);
	ft_strdel(&fc->s_cmd);
}

int		b_fc(t_cmd *cmd, t_shell *shell)
{
	t_fc_vars	fc;
	int			ret;

	(void)shell;
	fc_vars_init(&fc);
	if ((ret = fc_parse_options(cmd, &fc)) < 1 || !fc_parse_range(cmd, &fc)
		|| !fc_build_tab(&fc))
	{
		if (ret == -1)
		{
			ft_putstr_fd("fc: usage: fc [-e ename] [-nlr] [first] [last] o", 2);
			ft_putendl_fd("r fc -s [pat=rep] [cmd]", 2);
		}
		fc_vars_del(&fc);
		return (1);
	}
	fc_proceed(&fc);
	fc_vars_del(&fc);
	return (0);
}
