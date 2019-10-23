/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_is_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 17:38:56 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/23 18:10:22 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int			tok_is_redirection(t_token *token)
{
	if (!token)
		return (0);
	return (token->type == TOKEN_REDIRI
			|| token->type == TOKEN_REDIRO
			|| token->type == TOKEN_AGGR);
}
