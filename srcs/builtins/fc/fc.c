/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 17:13:15 by pcharrie          #+#    #+#             */
/*   Updated: 2019/11/12 05:56:26 by pcharrie         ###   ########.fr       */
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
	fc->from = -1;
	fc->to = -1;
	fc->list = 0;
	fc->exec = 0;
	fc->rm = 0;
	fc->rv = 0;
	fc->editor = NULL;
	fc->i = 0;
	fc->tab_len = 0;
	fc->tab = NULL;
}

void	fc_proceed(t_fc_vars *fc)
{
	if (fc->exec)
	{

	}
	else if (fc->list)
		fc_list(fc);
	else
	{
		// edit
	}
}

int		fc_build_tab_len(t_fc_vars *fc)
{
	int			i;
	int			j;
	t_histo_lst	*lst;

	lst = g_shell.history.lst;
	i = 0;
	j = 0;
	while (lst)
	{
		if (i >= fc->from)
		{
			if (fc->to > -1 && i > fc->to)
				break;
			j++;
		}
		i++;
		lst = lst->next;
	}
	return (j);
}

int		fc_build_tab(t_fc_vars *fc)
{
	int			i;
	int			j;
	t_histo_lst	*lst;

	fc->tab_len = fc_build_tab_len(fc);
	if (!(fc->tab = ft_2dstrnew(fc->tab_len)))
		return (0);
	lst = g_shell.history.lst;
	i = 0;
	j = 0;
	while (lst)
	{
		if (i >= fc->from)
		{
			if (fc->to > -1 && i > fc->to)
				break;
			if (!(fc->tab[j++] = ft_strdup(lst->str)))
			{
				ft_2dstrdel(&fc->tab);
				return (0);
			}
		}
		i++;
		lst = lst->next;
	}
	return (1);
}

void	fc_vars_del(t_fc_vars *fc)
{
	ft_2dstrdel(&fc->tab);
	ft_strdel(&fc->editor);
}

int		b_fc(t_cmd *cmd, t_shell *shell)
{
	t_fc_vars	fc;
	int			ret;

	fc_vars_init(&fc);
	if ((ret = fc_parse_options(cmd, &fc)) < 1 || !fc_parse_range(cmd, &fc)
		|| !fc_build_tab(&fc))
	{
		if (ret == -1)
			ft_putendl_fd("fc: usage: fc [-e ename] [-nlr] [first] [last] or fc -s [pat=rep] [cmd]", 2);
		fc_vars_del(&fc);
		return (1);
	}
	
	ft_printf("\nfrom: %d\n", fc.from);
	ft_printf("to: %d\n", fc.to);
	ft_printf("list: %d\n", fc.list);
	ft_printf("exec: %d\n", fc.exec);
	ft_printf("rm: %d\n", fc.rm);
	ft_printf("rv: %d\n", fc.rv);
	ft_printf("editor: %s\n", fc.editor);
	
	fc_proceed(&fc);
	fc_vars_del(&fc);
	return (0);
}
