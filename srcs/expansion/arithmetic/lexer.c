/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 18:00:22 by alagroy-          #+#    #+#             */
/*   Updated: 2019/11/05 14:15:16 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arithmetic.h"

char				*g_sym_tab[NBR_SYM] =\
{
	" \t\n",
	"$qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM",
	"1234567890",
	"+",
	"-",
	"*/%",
	"=",
	"!",
	"<>",
	"|",
	"&",
	"\0",
};

int					g_ae_lexer[2][10][NBR_SYM + 1] =\
{
	{
		{0, 1, 2, 3, 4, -4, 5, 6, 7, 8, 9, -9, -1},
		{-2, 1, 1, -12, -12, -12, -12, -12, -12, -12, -12, -12, -1},
		{-3, -1, 2, -13, -13, -13, -13, -13, -13, -13, -13, -13, -1},
		{-4, -14, -14, -5, -14, -1, -1, -1, -1, -1, -1, -1, -1},
		{-4, -14, -14, -14, -6, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -7, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -7, -1, -1, -1, -1, -1, -1},
		{-7, -1, -1, -1, -1, -1, -7, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -8, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -8, -1, -1},
	},
	{
		{0, 1, 2, 3, 4, -4, 5, 6, 7, 8, 9, -9, -1},
		{-2, 1, 1, -12, -12, -12, -12, -12, -12, -12, -12, -12, -1},
		{-3, -1, 2, -13, -13, -13, -13, -13, -13, -13, -13, -13, -1},
		{3, -14, 2, -5, -14, -1, -1, -1, -1, -1, -1, -1, -1},
		{4, -14, 2, -14, -6, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -7, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -7, -1, -1, -1, -1, -1, -1},
		{-7, -1, -1, -1, -1, -1, -7, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -8, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -8, -1, -1},
	},
};

t_fill_aevalue		g_ae_value_tab[NBR_AE_VAL] =\
{
	{"+", PLUS},
	{"++", PPLUS},
	{"-", MINUS},
	{"--", MMINUS},
	{"*", MULT},
	{"/", DIV},
	{"%", MOD},
	{"==", EQU},
	{"!=", NEQU},
	{">", GREAT},
	{">=", GREATEQ},
	{"<", LESS},
	{"<=", LESSEQ},
	{"&&", AND},
	{"||", OR},
};

static t_ae_token	fill_token(char *str, int begin, int *i, int state)
{
	t_ae_token	token;
	char		*sub;
	int			j;

	j = -1;
	ft_bzero(&token, sizeof(token));
	if (state < -10)
		*i -= 1;
	if (state < -10)
		state += 10;
	token.type = state * -1 - 1;
	if (token.type == ERROR || token.type == EOI
			|| !(sub = ft_strsub(str, begin, *i - begin)))
		return (token);
	if (token.type == NUM)
		token.num_value = ft_atol(sub);
	else if (token.type == WORD)
		token.num_value = 0;
	else
		while (++j < NBR_AE_VAL)
			if (!ft_strncmp(sub, g_ae_value_tab[j].str,
						ft_strlen(g_ae_value_tab[j].str)))
				token.value = g_ae_value_tab[j].value;
	token.type == WORD ? token.word = sub : ft_strdel(&sub);
	return (token);
}

static t_ae_token	make_next_aetoken(char *str, int new, int tab_i)
{
	static int	i = 0;
	int			j;
	int			begin;
	int			state;
	t_ae_token	token;

	new ? i = 0 : 0;
	state = 0;
	begin = -1;
	while (state >= 0)
	{
		j = -1;
		while (++j < NBR_SYM)
			if (ft_strchr(g_sym_tab[j], str[i]))
				break ;
		if (str[i] == '\0')
			j = NBR_SYM - 1;
		state = g_ae_lexer[tab_i][state][j];
		(state != 0 && begin == -1) ? begin = i : 0;
		i++;
	}
	token = fill_token(str, begin, &i, state);
	return (token);
}

t_list				*lex_ae_str(char *str)
{
	t_ae_token	token;
	t_list		*new;
	t_list		*begin;

	begin = NULL;
	token.type = OPERATOR;
	while (token.type != EOI && token.type != ERROR)
	{
		token = make_next_aetoken(str, begin ? 0 : 1,
				token.type != WORD && token.type != NUM && token.type != INCR
				&& token.type != DECR ? 1 : 0);
		if (!(new = ft_lstnew(&token, sizeof(t_token))))
			return (NULL);
		if (!begin)
			begin = new;
		else
			ft_lstend(&begin, new);
		if (((t_ae_token *)new->content)->type == ERROR
				|| ((t_ae_token *)new->content)->type == EOI)
			break ;
	}
	return (begin);
}
