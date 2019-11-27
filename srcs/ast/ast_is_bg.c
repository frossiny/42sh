/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_is_bg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 17:31:11 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/27 17:32:32 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		ast_is_bg(t_token *tokens)
{
	while (tok_is_cmd_comp(tokens))
		tokens = tokens->next;
	if (tokens && tokens->type == TOKEN_JOBS)
		return (1);
	return (0);
}
