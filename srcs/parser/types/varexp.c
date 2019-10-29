/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varexp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 16:27:34 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/29 16:46:23 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer.h"
#include "parser.h"
#include "variables.h"

int		par_type_varexp(t_parser *par)
{
	if (par->tokens->type == TOKEN_VARCLOSE)
	{
		par_next(par, 1);
		return (1);
	}
	if (!par->tokens->next || !par->tokens->next->next)
		return (0);
	if (par->tokens->next->next->type != TOKEN_VARCLOSE)
	{
		par_next(par, 2);
		return (0);
	}
	if (par->tokens->next->type != TOKEN_NAME \
		|| !var_is_key_valid(par->tokens->next->content, par->tokens->next->len))
	{
		ft_dprintf(2, "42sh: ${%s}: bad substitution\n", par->tokens->next->content);
		par_next(par, 1);
		return (-1);
	}
	par_next(par, 3);
	return (1);
}
