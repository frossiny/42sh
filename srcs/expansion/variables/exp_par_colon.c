/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_par_colon.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:20:01 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/21 15:24:55 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion.h"
#include "variables.h"
#include "shell.h"
#include "lexer.h"

int			exp_wordtok(t_token *tok)
{
	return (expand(tok, 0, NULL));
}

int			exp_word(t_expansion *exp, char **word)
{
	t_token	*tok;
	int		ret;
	size_t	osize;

	if (!(tok = (t_token *)malloc(sizeof(t_token))))
		return (0);
	tok->content = *word;
	tok->len = ft_strlen(*word);
	osize = tok->len;
	tok->type = TOKEN_NAME;
	tok->next = NULL;
	ret = exp_wordtok(tok);
	*word = tok->content;
	exp->i += osize;
	free(tok);
	return (ret);
}

int			exp_par_colon(t_expansion *exp, t_var *var, char *name)
{
	char	op;
	char	*word;
	int		ret;

	exp->i++;
	op = exp->str[exp->i++];
	word = exp_get_word(exp);
	if (!(ret = exp_word(exp, &word)))
		return (ret);
	if (op == '-')
		ret = exp_minus(exp, var, word, name);
	else if (op == '+')
		ret = exp_plus(exp, var, word, name);
	else if (op == '?')
		ret = exp_qm(exp, var, word, name);
	else if (op == '=')
		ret = exp_equ(exp, var, word, name);
	exp->i++;
	free(word);
	exp->li = exp->i;
	return (ret);
}
