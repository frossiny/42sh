/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_get_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 15:22:13 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/07 14:51:59 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "variables.h"
#include "expansion.h"

static t_var	*get_special_var(char *key)
{
	t_var	*ret;
	char	*tmp;

	if (!key)
		return (NULL);
	ret = NULL;
	if (ft_strequ(key, "?"))
	{
		tmp = ft_itoa(g_return);
		if (!(ret = var_new(key, tmp, 0)))
			return (NULL);
		free(tmp);
	}
	else if (ft_strequ(key, "$"))
	{
		tmp = ft_itoa((int)getpid());
		if (!(ret = var_new(key, tmp, 0)))
			return (NULL);
		free(tmp);
	}
	return (ret);
}

t_var			*exp_get_var(t_expansion *exp)
{
	t_var	*val;
	char	*key;

	key = exp_get_varname(exp);
	exp->i += ft_strlen(key);
	val = NULL;
	if ((val = get_special_var(key)))
	{
		free(key);
		return (val);
	}
	if (!(val = var_get(g_shell.vars, key)))
	{
		free(key);
		return (NULL);
	}
	free(key);
	return (val);
}
