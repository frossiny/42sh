/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_is_varexp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 16:23:35 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/20 15:03:29 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		tok_is_varexp(t_token *token)
{
	if (!token)
		return (0);
	if (token->type == TOKEN_VAR)
		return (1);
	return (0);
}
