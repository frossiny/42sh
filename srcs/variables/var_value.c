/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 15:29:41 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/01 15:30:46 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "variables.h"

char	*var_value(t_var *vars, char *key)
{
	t_var	*var;

	if (!(var = var_get(vars, key)))
		return (NULL);
	return (var->value);
}
