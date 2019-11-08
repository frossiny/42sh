/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 16:47:26 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/08 16:49:33 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "variables.h"

int		var_export(t_var *vars, char *key)
{
	t_var *var;

	if (!(var = var_get(vars, key)))
		return (0);
	var->export = 1;
	return (1);
}
