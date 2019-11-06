/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_par_colon.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:20:01 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/06 16:37:52 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion.h"
#include "variables.h"
#include "shell.h"

static int	exp_plus(t_expansion *exp, t_var *var, char *word, char *name)
{
	(void)name;
	if (!var || !var->value)
		return (1);
	exp_join(exp, ft_strdup(word));
	return (1);
}

static int	exp_qm(t_expansion *exp, t_var *var, char *word, char *name)
{
	if (!var || !var->value)
	{
		ft_dprintf(2, "42sh: %s: %s\n", name, word);
		return (0);
	}
	exp_join(exp, ft_strdup(var->value));
	return (1);
}

static int	exp_equ(t_expansion *exp, t_var *var, char *word, char *name)
{
	if (!var || !var->value)
	{
		var_set(&(g_shell.vars), name, word, 0);
		var = var_get(g_shell.vars, name);
	}
	exp_join(exp, ft_strdup(var->value));
	return (1);
}

static int	exp_minus(t_expansion *exp, t_var *var, char *word, char *name)
{
	(void)name;
	if (!var || !var->value)
		exp_join(exp, ft_strdup(word));
	else
		exp_join(exp, ft_strdup(var->value));
	return (1);
}

int			exp_par_colon(t_expansion *exp, t_var *var, char *name)
{
	char	*word;
	int		ret;

	exp->i++;
	word = ft_strsub(exp->str, exp->i + 1,
			(ft_strchr(exp->str + exp->i + 1, '}') - exp->str - exp->i - 1));
	if (exp->str[exp->i] == '-')
		ret = exp_minus(exp, var, word, name);
	else if (exp->str[exp->i] == '+')
		ret = exp_plus(exp, var, word, name);
	else if (exp->str[exp->i] == '?')
		ret = exp_qm(exp, var, word, name);
	else if (exp->str[exp->i] == '=')
		ret = exp_equ(exp, var, word, name);
	exp->i = ft_strchr(exp->str, '}') - exp->str;
	exp->i++;
	exp->li = exp->i;
	free(word);
	return (ret);
}
