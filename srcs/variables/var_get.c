/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 19:10:03 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/14 19:12:02 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "variables.h"

t_var	*var_get(t_var *vars, char *key)
{
	if (!vars || !key)
		return (NULL);
	while (vars)
	{
		if (ft_strequ(vars->key, key))
			return (vars);
		vars = vars->next;
	}
	return (NULL);
}
