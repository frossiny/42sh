/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_destroy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 16:31:20 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/17 16:31:55 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	tok_destroy(t_token *token)
{
	t_token *next;

	next = NULL;
	while (token)
	{
		next = token->next;
		free(token->content);
		free(token);
		token = next;
	}
}
