/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_replace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 18:02:39 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/14 19:04:28 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "variables.h"

int		var_replace(t_var *var, char *value)
{
	if (!var)
		return (0);
	free(var->value);
	if (!(var->value = ft_strdup(value)))
		return (0);
	return (1);
}
