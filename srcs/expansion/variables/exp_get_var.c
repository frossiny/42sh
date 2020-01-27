/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_get_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 15:22:13 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/23 15:20:03 by frossiny         ###   ########.fr       */
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
			g_lpid = 0;
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

t_var			*exp_get_var(t_expansion *exp, size_t *key_len)
{
	t_var	*val;
	char	*key;
	size_t	len;

	key = exp_get_varname(exp);
	len = ft_strlen(key);
	if (key_len)
		*key_len = len;
	exp->i += len;
	val = NULL;
	if (!(val = get_special_var(key)))
		val = var_dup(var_get(g_shell.vars, key));
	free(key);
	return (val);
}
