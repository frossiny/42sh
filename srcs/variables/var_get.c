/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 19:10:03 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/20 18:32:00 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "variables.h"

char	*var_get_value(t_var *vars, char *key)
{
	if (!vars || !key)
		return (NULL);
	while (vars && vars->key)
	{
		if (ft_strequ(vars->key, key))
			return (ft_strdup(vars->value));
		vars = vars->next;
	}
	return (NULL);
}

t_var	*var_get(t_var *vars, char *key)
{
	if (!vars || !key)
		return (NULL);
	while (vars && vars->key)
	{
		if (ft_strequ(vars->key, key))
			return (vars);
		vars = vars->next;
	}
	return (NULL);
}
