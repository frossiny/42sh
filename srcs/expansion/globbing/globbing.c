/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globbing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 17:28:24 by vsaltel           #+#    #+#             */
/*   Updated: 2019/11/21 16:45:21 by frossiny         ###   ########.fr       */
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
	t_globbing	glob;

	if (!token || !(token->content))
		return (0);
	if (!(token->content))
		return (0);
	glob.nb_file = 0;
	if (tok_is_word(token) && is_glob_str(token->content))
	{
		set_glob(&glob, token);
		dir_globbing(&glob, glob.list, glob.root
			? ft_strdup("/") : ft_strdup("./"));
		free_globbing(glob.list);
	}
	if (glob.nb_file)
		remove_first_token(token);
	return (glob.nb_file ? 1 : 0);
}
