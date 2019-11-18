/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_simple_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 14:24:33 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/18 16:36:21 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"
#include "variables.h"
#include "expansion.h"

int			exp_simple_var(t_expansion *exp)
{
	size_t	vsize;
	t_var	*var;

	if (!exp)
		return (0);
	if (exp->li > exp->i)
		exp_join(exp, ft_strsub(exp->str, exp->li, exp->i - exp->li), 1);
	exp->li = exp->i;
	if (exp->str[exp->i] != '$')
		return (0);
	exp->i++;
	if ((var = exp_get_var(exp)))
		exp_join(exp, ft_strdup(var->value), 1);
	else
		exp->i += get_var_size(exp->str + exp->i);
	exp->li = exp->i;
	return (0);
}
