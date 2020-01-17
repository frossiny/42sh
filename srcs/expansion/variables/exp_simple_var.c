/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_simple_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 14:24:33 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/17 18:04:37 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"
#include "variables.h"
#include "expansion.h"

static char	*dup_escape(char *src, t_expansion *exp)
{
	char	*dst;
	size_t	i;

	if (!(dst = (char *)malloc(ft_strlen(src) * 2 + 1)))
		return (NULL);
	i = 0;
	while (*src)
	{
		if (!exp->isquote)
			dst[i++] = '\\';
		dst[i++] = *src;
		src++;
	}
	dst[i] = '\0';
	return (dst);
}

int			exp_simple_var(t_expansion *exp)
{
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
	{
		exp_join(exp, dup_escape(var->value, exp), 1);
		var_destroy(&var);
	}
	else
		exp->i += get_var_size(exp->str + exp->i);
	exp->li = exp->i;
	return (0);
}
