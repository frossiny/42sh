/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_tok_clean.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 14:35:42 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/21 15:35:22 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "lexer.h"

void	exp_tok_clean(t_token *token)
{
	t_token	*prev;
	t_token	*curr;
	t_token	*next;

	prev = NULL;
	curr = g_shell.lexer.tokens;
	while (curr)
	{
		next = curr->next;
		if (curr == token)
		{
			curr = NULL;
			if (!prev)
				g_shell.lexer.tokens = next;
			else
				prev->next = next;
			break ;
		}
		else
			prev = curr;
		curr = next;
	}
}
