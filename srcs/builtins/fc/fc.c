/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 17:13:15 by pcharrie          #+#    #+#             */
/*   Updated: 2020/02/19 17:33:47 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "variables.h"
#include "builtins.h"

static void	fc_vars_init(t_shell *shell, t_fc_vars *fc)
{
	fc->from = shell->history.size - 1 - 15;
	fc->to = shell->history.size - 1;
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

static void	fc_proceed(t_shell *shell, t_fc_vars *fc)
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
		if (!fc->editor)
			if (!(fc->editor = var_get_value(shell->vars, "FCEDIT")))
				if (!(fc->editor = ft_strdup("/bin/ed")))
					return ;
		fc_edit(fc);
	}
}

static void	fc_vars_del(t_fc_vars *fc)
{
	ft_2dstrdel(&fc->tab);
	ft_2dstrdel(&fc->ed_args);
	ft_strdel(&fc->editor);
	ft_strdel(&fc->s_cmd);
}

int			b_fc(t_cmd *cmd, t_shell *shell)
{
	t_fc_vars	fc;
	int			ret;

	fc_vars_init(shell, &fc);
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
	fc_proceed(shell, &fc);
	fc_vars_del(&fc);
	return (0);
}
