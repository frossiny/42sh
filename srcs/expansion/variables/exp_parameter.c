/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_parameter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 15:10:45 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/04 16:08:52 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion.h"
#include "shell.h"
#include "variables.h"

static t_var	*getvar(t_expansion *exp, size_t vsize)
{
	t_var	*var;
	char	*tmp;

	if (!(tmp = ft_strsub(exp->str, exp->i, vsize)))
		return (NULL);
	var = var_get(g_shell.vars, tmp);
	free(tmp);
	return (var);
}

static size_t	parse_opt(t_expansion *exp, t_var *var, size_t i)
{
	if (exp->str[i] == '}')
	{
		var && var->value ? exp_join(exp, ft_strdup(var->value)) : 0;
		i++;
	}
	else if (exp->str[i] == ':')
	{
		i++;
		if (exp->str[i] == '}')
			return (i + 1);
		if (exp->str[i] == '-')
		{
			i++;
			var && var->value ? exp_join(exp, ft_strdup(var->value)) :
				exp_join(exp, ft_strsub(exp->str, i, ft_strchr(exp->str + i, '}') - exp->str + i));
		}
	}
	return (i);
}

int				exp_parameter(t_expansion *exp)
{
	size_t	vsize;
	char	*tmp;
	
	if (!exp || !ft_strnequ(exp->str + exp->i, "${", 2))
		return (0);
	if (exp->li > exp->i)
		exp_join(exp, ft_strsub(exp->str, exp->li, exp->i - exp->li));
	exp->i += 2;
	if (!(vsize = get_var_size(exp->str + exp->i)))
		return (0);
	exp->i += parse_opt(exp, getvar(exp, vsize), exp->i + vsize + 1);
	exp->li = exp->i;
	return (1);
}
