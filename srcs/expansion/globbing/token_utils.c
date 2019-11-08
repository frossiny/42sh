/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 13:41:50 by vsaltel           #+#    #+#             */
/*   Updated: 2019/10/30 13:23:54 by vsaltel          ###   ########.fr       */
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

void			remove_first_token(t_token **token)
{
	t_token *tmp;
	t_token *curr;

	curr = *token;
	free(curr->content);
	curr->content = curr->next->content;
	tmp = curr->next;
	curr->next = curr->next->next;
	free(tmp);
	*token = curr->next;
}

void			remove_token(t_token *curr)
{
	t_token *prev;
	t_token *beg;

	beg = curr;
	prev = NULL;
	while (curr)
	{
		if (is_glob_str(curr->content) && curr->is_glob_sub)
		{
			if (curr == beg)
				remove_first_token(&curr);
			else
			{
				prev->next = curr->next;
				free_token(curr);
				curr = prev->next;
			}
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
}
