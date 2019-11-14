/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_parameter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 15:10:45 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/13 15:25:43 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion.h"
#include "shell.h"
#include "variables.h"

static void		clean_var(t_var *var)
{
	if (!var)
		return ;
	if (var_is_key_valid(var->key, ft_strlen(var->key)))
		return ;
	var_delete(&var, var->key);
}

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

static int		exp_noflag(t_expansion *exp, t_var *var, char *name)
{
	(void)name;
	if (!var || !var->value)
		return (1);
	exp_join(exp, ft_strdup(var->value));
	exp->i++;
	exp->li = exp->i;
	return (1);
}

int				exp_parameter(t_expansion *exp)
{
	int		ret;
	t_var	*var;
	char	*tmp;
	char	*name;

	if (!exp || !ft_strnequ(exp->str + exp->i, "${", 2))
		return (0);
	if (exp->li > exp->i)
		exp_join(exp, ft_strsub(exp->str, exp->li, exp->i - exp->li));
	exp->i += 2;
	if (exp->str[exp->i] == '#')
	{
		exp->i++;
		exp_join(exp, exp_par_len(exp));
		return (1);
	}
	name = exp_get_varname(exp);
	var = exp_get_var(exp);
	if (exp->str[exp->i] == ':')
		ret = exp_par_colon(exp, var, name);
	else if (exp->str[exp->i] == '#' || exp->str[exp->i] == '%')
		ret = exp_del_pattern(exp, var);
	else
		ret = exp_noflag(exp, var, name);
	free(name);
	clean_var(var);
	return (ret);
}
