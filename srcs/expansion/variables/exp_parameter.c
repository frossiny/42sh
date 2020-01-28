/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_parameter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 15:10:45 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/23 15:18:25 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion.h"
#include "shell.h"
#include "variables.h"

static void		clean_var(t_var *var, char *name)
{
	free(name);
	if (!var)
		return ;
	if (var_is_key_valid(var->key, ft_strlen(var->key)))
		return ;
	var_delete(&var, var->key);
}

static int		exp_noflag(t_expansion *exp, t_var *var, char *name)
{
	(void)name;
	if (!var || !var->value)
	{
		exp->li += 2 + ft_strlen(name) + 1;
		exp->i = exp->li;
		return (1);
	}
	exp_join(exp, exp_dup_escape(var->value, exp), 1);
	exp->i++;
	exp->li = exp->i;
	return (1);
}

int				exp_parameter(t_expansion *exp)
{
	int		ret;
	t_var	*var;
	char	*name;

	if (!exp_parameter_parse(exp))
		return (0);
	if (exp->li > exp->i)
		exp_join(exp, ft_strsub(exp->str, exp->li, exp->i - exp->li), 1);
	exp->i += 2;
	if (exp->str[exp->i] == '#' && exp->i++)
	{
		exp_join(exp, exp_par_len(exp), 1);
		return (1);
	}
	name = exp_get_varname(exp);
	var = exp_get_var(exp, NULL);
	if (exp->str[exp->i] == ':')
		ret = exp_par_colon(exp, var, name);
	else if (exp->str[exp->i] == '#' || exp->str[exp->i] == '%')
		ret = exp_del_pattern(exp, var);
	else
		ret = exp_noflag(exp, var, name);
	clean_var(var, name);
	var_destroy(&var);
	return (ret);
}
