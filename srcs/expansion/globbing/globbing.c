/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 18:49:27 by vsaltel           #+#    #+#             */
/*   Updated: 2019/10/28 14:20:32 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "lexer.h"
#include "libft.h"

int			replace_globing(t_token *token, t_var *vars)
{
	t_token		*begin;
	t_token		*token_next;
	char		*tmp;
	t_globing	glob;
	int		ret;

	begin = token;
	while (token)
	{
		ret = 0;
		token_next = token->next;
		if (is_word_token(token) && is_glob_str(token->content))
		{
			glob.nb_file = 0;
			glob.token = token;
			glob.root = (token->content[0] == '/');
			glob.list = create_globing(pull_multi_occ(token->content, '*'));	
			ret = dir_globing(&glob, glob.list, glob.root ? ft_strdup("/") : ft_strdup("./"));
			token->is_glob_sub = glob.nb_file;
			free_globing(glob.list);
		}
		token = token_next;
	}
	remove_token(begin);
	return (ret);
}
