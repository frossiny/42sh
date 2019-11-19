/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 06:32:15 by pcharrie          #+#    #+#             */
/*   Updated: 2019/11/19 04:38:47 by pcharrie         ###   ########.fr       */
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

static int	fc_build_tab_len(t_fc_vars *fc)
{
	int			i;
	int			j;
	t_histo_lst	*lst;

	if ((lst = g_shell.history.lst))
		lst = lst->next;
	i = fc_histo_lst_size();
	j = 0;
	while (lst)
	{
		if (i >= fc->from)
		{
			if (fc->to < 0 || !(fc->to > -1 && i > fc->to))
				j++;
		}
		i--;
		lst = lst->next;
	}
	return (j);
}

int			fc_build_tab(t_fc_vars *fc)
{
	int			i;
	int			j;
	t_histo_lst	*lst;

	fc->tab_len = fc_build_tab_len(fc);
	if (!(fc->tab = ft_2dstrnew(fc->tab_len)))
		return (0);
	if ((lst = g_shell.history.lst))
		lst = lst->next;
	i = fc_histo_lst_size();
	j = 0;
	while (lst)
	{
		if (i >= fc->from && (fc->to < 0 || !(fc->to > -1 && i > fc->to))
			&& !(fc->tab[j++] = ft_strdup(lst->str)))
		{
			ft_2dstrdel(&fc->tab);
			return (0);
		}
		i--;
		lst = lst->next;
	}
	return (1);
}

void		fc_set_exec_cmd(t_fc_vars *fc)
{
	t_histo_lst	*lst;
	int			i;

	ft_2dstrdel(&fc->tab);
	if ((lst = g_shell.history.lst))
		lst = lst->next;
	i = fc_histo_lst_size();
	while (lst)
	{
		if (ft_strstr(lst->str, fc->s_cmd))
		{
			fc->from = i;
			fc->to = i;
			fc_build_tab(fc);
			return ;
		}
		i--;
		lst = lst->next;
	}
	ft_putendl_fd("42sh: fc: command not found", 2);
}
