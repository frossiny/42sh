/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globbing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 17:28:24 by vsaltel           #+#    #+#             */
/*   Updated: 2019/11/19 17:28:27 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "lexer.h"
#include "libft.h"

void		set_glob(t_globbing *glob, t_token *token)
{
	glob->nb_file = 0;
	glob->token = token;
	glob->root = (token->content[0] == '/');
	glob->list = create_globbing(pull_multi_occ(token->content, '*'));
}

int			replace_globbing(t_token *token)
{
	t_token		*begin;
	t_token		*token_next;
	t_globbing	glob;

	begin = token;
	while (token)
	{
		token_next = token->next;
		if (tok_is_word(token) && is_glob_str(token->content))
		{
			//ft_printf("token->%s, %p, %p\n", token->content, token, token_next);
			set_glob(&glob, token);
			dir_globbing(&glob, glob.list, glob.root
				? ft_strdup("/") : ft_strdup("./"));
			token->is_glob_sub = glob.nb_file;
			free_globbing(glob.list);
			//ft_printf("token->%s, %p, %p\n", token->content, token, token_next);
		}
		token = token_next;
	}
	remove_token(begin);
	return (glob.nb_file ? 0 : 1);
}
