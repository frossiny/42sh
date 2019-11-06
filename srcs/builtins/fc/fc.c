/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 17:13:15 by pcharrie          #+#    #+#             */
/*   Updated: 2019/11/06 18:04:35 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "utils.h"
#include "shell.h"
#include "libft.h"
#include "variables.h"
#include "builtins.h"
#include "opt.h"

void	fc_print_history(int min, int max)
{
	int			i;
	t_histo_lst	*lst;

	i = 0;
	lst = g_shell.history.lst;
	while (lst)
	{
		i++;
		if (i >= min && (max < 0 ? 1 : i <= max))
			ft_printf("%d     %s\n", i, lst->str);
		lst = lst->next;
	}
}

char 	*fc_get_editor(t_cmd *cmd)
{
	
}

int		b_fc(t_cmd *cmd, t_shell *shell)
{
	t_options *opts;

	
	return (0);
}
