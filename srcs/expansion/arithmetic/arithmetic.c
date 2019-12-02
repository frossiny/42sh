/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 13:40:41 by alagroy-          #+#    #+#             */
/*   Updated: 2019/12/02 18:44:24 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arithmetic.h"
#include "expansion.h"

static void	find_ae_limits(char *str, int *beg, int *end)
{
	int		i;
	int		bool;

	bool = -1;
	i = -1;
	while (str[++i])
	{
		if (!ft_strncmp(str + i, "$((", 3))
		{
			bool++;
			if (!bool)
				*beg = i;
			i += 2;
		}
		if (!ft_strncmp(str + i, "))", 2))
		{
			if (!bool)
			{
				*end = i;
				break ;
			}
			i++;
			bool--;
		}
	}
}

static int	check_incr(char *str)
{
	int		i;
	int		j;

	i = -1;
	while (str[++i])
		if (!ft_strncmp(str + i, "++", 2) || !ft_strncmp(str + i, "--", 2))
		{
			j = i - 1;
			while (j > 0 && ft_isalnum(str[j]))
				j--;
			if (j == 0 && ft_isdigit(str[j]))
				return (ft_dprintf(2,
							"42sh: syntax error: operand expected\n") * 0);
			else if (ft_isdigit(str[j + 1]))
				return (ft_dprintf(2,
							"42sh: syntax error: operand expected\n") * 0);
		}
	return (1);
}

int			ae_process(t_token *token)
{
	t_list	*token_list;
	char	*str;
	int		status;
	long	result;

	if (!check_incr(token->content) ||
			!(str = ae_base10(ft_strdup(token->content))))
		return (0);
	if (!(token_list = lex_ae_str(str))
			|| (status = parse_aetoken(token_list) != AEPSUCCESS))
	{
		ft_dprintf(2, "42sh: syntax error in expression\n");
		ft_strdel(&token->content);
		ft_strdel(&str);
		ft_lstdel(&token_list, del_ae_token);
		token->content = ft_strnew(0);
		return (0);
	}
	result = eval_ae(token_list);
	eval_var(token->content);
	ft_strdel(&token->content);
	ft_strdel(&str);
	ft_lstdel(&token_list, del_ae_token);
	token->content = ft_ltoa(result);
	return (1);
}

int			replace_ae_token(t_token *token)
{
	t_token	tmp;
	int		beg;
	int		end;

	beg = -1;
	end = -1;
	tmp.next = NULL;
	find_ae_limits(token->content, &beg, &end);
	if (beg == -1 || end == -1)
		return (1);
	tmp.type = TOKEN_NAME;
	tmp.content = ft_strsub(token->content, beg + 3, end - beg - 3);
	tmp.len = ft_strlen(tmp.content);
	if (!(expand(&tmp, 0, NULL)))
		return (0);
	if (!(ae_process(&tmp)))
		return (0);
	token->content = ft_strdelpart(token->content, beg, end - beg + 2);
	token->content = ft_insert_str(token->content, tmp.content, beg);
	token->len = ft_strlen(token->content);
	return (replace_ae_token(token));
}
