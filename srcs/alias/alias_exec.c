/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:55:33 by vsaltel           #+#    #+#             */
/*   Updated: 2020/01/15 14:29:14 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alias.h"
#include "shell.h"
#include "structs.h"
#include "lexer.h"

int				alias_exec(t_shell *shell, char **input)
{
	int			ret;
	int			alias_ret;
	t_string	*alias_hist;

	ret = 0;
	alias_hist = NULL;
	alias_ret = alias_resolve(shell->lexer.tokens, shell->alias, &alias_hist);
	while (alias_ret > 0)
	{
		tok_to_input(input, shell->lexer.tokens);
		lexer_free(&(shell->lexer));
		if ((ret = lex_build(shell, input)) != 1)
		{
			free_alias_history(&alias_hist);
			return (ret);
		}
		alias_ret = alias_resolve(shell->lexer.tokens, shell->alias,
															&alias_hist);
	}
	free_alias_history(&alias_hist);
	return (0);
}
