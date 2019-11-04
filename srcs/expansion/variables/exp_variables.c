/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 15:42:26 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/04 15:48:39 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer.h"
#include "variables.h"
#include "expansion.h"

int		exp_variables(t_token *token)
{
	t_expansion	exp;

	if (!token || !token->content)
		return (0);
	exp_set_struct(&exp, token->content);
	while (exp.str[++(exp.i)])
	{
		if (exp.str[exp.i] == '\'')
			exp.isquote = !exp.isquote;
		if (exp.str[exp.i] != '$' || exp.isquote)
			continue ;
		if (exp.i > exp.li)
			exp_join(&exp, ft_strsub(exp.str, exp.li, exp.i - exp.li));
		if (ft_strnequ(exp.str + exp.i, "${", 2))
		{
			if (!exp_parameter(&exp))
			{
				ft_dprintf(2, "42sh: bad substitution\n");
				return (0);
			}
		}
		else
			exp_simple_var(&exp);
		if (!exp.str[exp.i])
			break ;
	}
	if (exp.i > exp.li)
		exp_join(&exp, ft_strsub(exp.str, exp.li, exp.i - exp.li));
	exp.new = exp.new ? exp.new : ft_strdup("");
	tok_replace(token, exp.new);
	return (1);
}
