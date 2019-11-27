/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 13:41:50 by vsaltel           #+#    #+#             */
/*   Updated: 2019/11/20 15:08:08 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "expansion.h"

void			free_token(t_token *token)
{
	free(token->content);
	free(token);
}

void			add_token(t_globbing *glob, char *content)
{
	t_token *new;

	if (!(new = (t_token *)malloc(sizeof(t_token))))
		return ;
	if (!glob->root)
		new->content = ft_strdup(content + 2);
	else
		new->content = ft_strdup(content);
	new->next = glob->token->next;
	new->len = ft_strlen(new->content);
	new->type = TOKEN_NAME;
	glob->token->next = new;
	glob->token = new;
	free(content);
	glob->nb_file++;
}

void			remove_first_token(t_token *token)
{
	t_token *tmp;

	if (!token || !(token->next))
		return ;
	free(token->content);
	token->content = token->next->content;
	token->len = token->next->len;
	tmp = token->next;
	token->next = token->next->next;
	free(tmp);
}
