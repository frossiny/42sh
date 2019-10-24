/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 13:29:22 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/24 12:56:39 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "variables.h"

static int	need_quoting(char *val)
{
	const char	*cl = " ?|&;<>$`\\\"'\t\n";
	int			i;

	i = 0;
	while (val[i])
	{
		if (ft_strchr(cl, val[i]))
			return (1);
		i++;
	}
	return (0);
}

int			var_display(t_var *vars)
{
	if (!vars)
		return (0);
	while (vars)
	{
		if (need_quoting(vars->value))
			ft_printf("%s='%s'\n", vars->key, vars->value);
		else
			ft_printf("%s=%s\n", vars->key, vars->value);
		vars = vars->next;
	}
	return (0);
}
