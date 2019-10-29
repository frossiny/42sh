/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_is_varexp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 16:23:35 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/29 16:24:54 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		tok_is_varexp(t_token *token)
{
	if (token->type == TOKEN_VAR)
		return (1);
	if (token->type == TOKEN_VAROPEN || token->type == TOKEN_VARCLOSE)
		return (1);
	return (0);
}
