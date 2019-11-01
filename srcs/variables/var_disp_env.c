/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_disp_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 13:44:46 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/17 13:45:07 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "variables.h"

int		var_disp_env(t_var *vars)
{
	if (!vars)
		return (0);
	while (vars)
	{
		if (vars->export)
		{
			if (vars->value)
				ft_printf("export %s=\"%s\"\n", vars->key, vars->value);
			else
				ft_printf("export %s\n", vars->key);
		}
		vars = vars->next;
	}
	return (0);
}
