/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 15:42:26 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/06 16:32:55 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer.h"
#include "variables.h"
#include "expansion.h"

static int	exp_var_loop(t_expansion *exp)
{
	while (exp->str[++(exp->i)])
	{
		if (exp->str[exp->i] == '\'')
			exp->isquote = !exp->isquote;
		if (exp->str[exp->i] != '$' || exp->isquote)
			continue ;
		if (exp->i > exp->li)
			exp_join(exp, ft_strsub(exp->str, exp->li, exp->i - exp->li));
		exp->li = exp->i;
		if (ft_strnequ(exp->str + exp->i, "${", 2))
		{
			if (!exp_parameter(exp))
				return (0);
		}
		else
			exp_simple_var(exp);
		if (exp->i >= ft_strlen(exp->str))
			break ;
	}
	if (exp->i > exp->li)
		exp_join(exp, ft_strsub(exp->str, exp->li, exp->i - exp->li));
	return (1);
}

int			exp_variables(t_token *token)
{
	t_expansion	exp;

	if (!token || !token->content)
		return (0);
	exp_set_struct(&exp, token->content);
	if (!exp_var_loop(&exp))
		return (0);
	tok_replace(token, exp.new ? exp.new : ft_strdup(""));
	return (1);
}
