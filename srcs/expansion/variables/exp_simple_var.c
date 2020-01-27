/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_simple_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 14:24:33 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/27 12:53:58 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"
#include "variables.h"
#include "expansion.h"

int		exp_simple_var(t_expansion *exp)
{
	t_var	*var;
	size_t	key_len;

	if (!exp)
		return (0);
	if (exp->li > exp->i)
		exp_join(exp, ft_strsub(exp->str, exp->li, exp->i - exp->li), 1);
	exp->li = exp->i;
	if (exp->str[exp->i] != '$')
		return (0);
	exp->i++;
	if ((var = exp_get_var(exp, &key_len)))
	{
		exp_join(exp, exp_dup_escape(var->value, exp), 1);
		var_destroy(&var);
	}
	else
	{
		key_len ? exp->i += get_var_size(exp->str + exp->i) \
			: exp_join(exp, ft_strdup("$"), 1);
	}
	exp->li = exp->i;
	return (0);
}
