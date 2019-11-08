/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_get_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 15:22:13 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/08 17:24:16 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "variables.h"
#include "expansion.h"

static t_var	*get_special_var_pid(char *key)
{
	t_var	*ret;
	char	*tmp;

	ret = NULL;
	if (ft_strequ(key, "$"))
	{
		tmp = ft_itoa((int)getpid());
		ret = var_new(key, tmp, 0);
		free(tmp);
	}
	else if (ft_strequ(key, "!"))
	{
		if (g_lpid < 0)
			return (NULL);
		tmp = ft_itoa(g_lpid);
		ret = var_new(key, tmp, 0);
		free(tmp);
	}
	return (ret);
}

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
		ret = var_new(key, tmp, 0);
		free(tmp);
	}
	else if (ft_strequ(key, "0"))
		ret = var_new(key, "42sh", 0);
	else
		ret = get_special_var_pid(key);
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
