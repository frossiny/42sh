/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_replace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 18:02:39 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/18 15:11:50 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "variables.h"

int		var_replace(t_var *var, char *value)
{
	if (!var)
		return (0);
	free(var->value);
	if (!value)
		var->value = ft_strdup("");
	else if (!(var->value = ft_strdup(value)))
		return (0);
	return (1);
}
