/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_disp_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 13:44:46 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/16 13:47:38 by frossiny         ###   ########.fr       */
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
			ft_printf("%s=%s\n", vars->key, vars->value);
		vars = vars->next;
	}
	return (0);
}
