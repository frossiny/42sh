/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 13:29:22 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/16 13:48:56 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "variables.h"

int		var_display(t_var *vars)
{
	if (!vars)
		return (0);
	while (vars)
	{
		ft_printf("%s=%s\n", vars->key, vars->value);
		vars = vars->next;
	}
	return (0);
}
