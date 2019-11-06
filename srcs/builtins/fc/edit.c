/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 18:04:37 by pcharrie          #+#    #+#             */
/*   Updated: 2019/11/06 18:42:17 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "utils.h"
#include "shell.h"
#include "libft.h"
#include "variables.h"
#include "builtins.h"
#include "opt.h"

void	fc_edit_history_file(char **tab)
{
	
}

void	fc_edit_history(int min, int max)
{
	char	**tab;
	int		i;
	int		j;
	
	if (!(tab = ft_2dstrnew(max > 0 ? max - min : 1)))
		return ;
	i = 0;
	j = 0;
	lst = g_shell.history.lst;
	while (lst)
	{
		i++;
		if (max < 0 && i == min)
		{
			if (!(tab[j++] = ft_strdup(lst->str)))
				return ft_2dstrdel(&tab);
			break ;
		}
		else if (i >= min && i <= max))
			if (!(tab[j++] = ft_strdup(lst->str)))
				return ft_2dstrdel(&tab);
		lst = lst->next;
	}
	fc_edit_history_file(tab);
}