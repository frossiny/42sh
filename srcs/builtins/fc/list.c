/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 01:29:44 by pcharrie          #+#    #+#             */
/*   Updated: 2019/11/12 05:28:45 by pcharrie         ###   ########.fr       */
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

void	fc_list_print(t_fc_vars *fc)
{
	int i;
	int j;

	i = 0;
	j = fc->from;
	while (fc->tab[i])
		(fc->rm ? ft_printf("	%s\n", fc->tab[i++])
			: ft_printf("%d	%s\n", j++, fc->tab[i++]));
}


void	fc_list_print_reverse(t_fc_vars *fc)
{
	int i;
	int j;

	i = fc->tab_len - 1;
	j = fc->from + i;
	while (i >= 0)
		(fc->rm ? ft_printf("	%s\n", fc->tab[i--])
			: ft_printf("%d	%s\n", j--, fc->tab[i--]));
}

void	fc_list(t_fc_vars *fc)
{
	(fc->rv ? fc_list_print_reverse(fc) : fc_list_print(fc));
}
