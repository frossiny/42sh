/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_simple_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 14:24:33 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/06 16:14:17 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"
#include "variables.h"
#include "expansion.h"

static char	*handle_var(t_var *vars, char *var_name)
{
	char	*ret;
	t_var	*var;

	ret = NULL;
	var = var_get(vars, var_name);
	if (var_name[0] == '?')
		ret = ft_itoa(g_return);
	else if (!var)
		ret = NULL;
	else
		ret = ft_strdup(var->value);
	free(var_name);
	return (ret);
}

int			exp_simple_var(t_expansion *exp)
{
	size_t	vsize;
	char	*tmp;

	if (!exp)
		return (0);
	if (exp->li > exp->i)
		exp_join(exp, ft_strsub(exp->str, exp->li, exp->i - exp->li));
	exp->li = exp->i;
	if (exp->str[exp->i] != '$')
		return (0);
	vsize = get_var_size(exp->str + exp->i);
	if (vsize > 0)
	{
		tmp = handle_var(g_shell.vars,
							ft_strsub(exp->str, exp->i + 1, vsize));
		tmp ? exp_join(exp, tmp) : 0;
		exp->i += vsize + 1;
		exp->li = exp->i;
	}
	return (0);
}
