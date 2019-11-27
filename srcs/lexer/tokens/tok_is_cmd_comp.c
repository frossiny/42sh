/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_is_cmd_comp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 12:12:40 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/26 12:14:28 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		tok_is_cmd_comp(t_token *token)
{
	if (!token)
		return (0);
	return (tok_is_word(token) || token->type == TOKEN_ASSIGNMENT
			|| tok_is_redirection(token));
}
