/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_par_colon_op.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 13:12:49 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/18 16:36:10 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "expansion.h"
#include "variables.h"
#include "libft.h"

int	exp_plus(t_expansion *exp, t_var *var, char *word, char *name)
{
	(void)name;
	if (!var || !var->value)
		return (1);
	exp_join(exp, ft_strdup(word), 1);
	return (1);
}

int	exp_qm(t_expansion *exp, t_var *var, char *word, char *name)
{
	if (!var || !var->value)
	{
		ft_dprintf(2, "42sh: %s: %s\n", name, word);
		return (0);
	}
	exp_join(exp, ft_strdup(var->value), 1);
	return (1);
}

int	exp_equ(t_expansion *exp, t_var *var, char *word, char *name)
{
	if (!var || !var->value)
	{
		var_set(&(g_shell.vars), name, word, 1);
		var = var_get(g_shell.vars, name);
	}
	exp_join(exp, ft_strdup(var->value), 1);
	return (1);
}

int	exp_minus(t_expansion *exp, t_var *var, char *word, char *name)
{
	(void)name;
	if (!var || !var->value)
		exp_join(exp, ft_strdup(word), 1);
	else
		exp_join(exp, ft_strdup(var->value), 1);
	return (1);
}
