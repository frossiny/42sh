/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_get_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 15:22:13 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/01 15:31:39 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "variables.h"

static char		*get_special_var(char *key)
{
	if (ft_strequ(key, "?"))
		return (ft_itoa(g_return));
	return (NULL);
}

char			*exp_get_var(char *key)
{
	char	*val;

	if ((val = get_special_var(key)))
		return (val);
	if (!(val = var_value(g_shell.vars, key)))
		return (NULL);
	return (ft_strdup(val));
}
