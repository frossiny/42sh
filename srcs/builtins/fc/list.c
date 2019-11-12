/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 01:29:44 by pcharrie          #+#    #+#             */
/*   Updated: 2019/11/12 02:18:36 by pcharrie         ###   ########.fr       */
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

void	fc_list(t_fc_vars *fc)
{
	t_histo_lst	*lst;
	int			i;

	lst = g_shell.history.lst;
	i = 0;
	while (lst)
	{
		if (i >= fc->from)
		{
			if (fc->to > -1 && i > fc->to)
				break;
			(fc->rm ? ft_printf("	%s\n", lst->str)
				: ft_printf("%d	%s\n", i, lst->str));
		}
		i++;
		lst = lst->next;
	}
}
