/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 18:04:45 by alagroy-          #+#    #+#             */
/*   Updated: 2019/11/08 17:07:48 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arithmetic.h"

t_list		*copy_ae_token(t_list *elem)
{
	t_ae_token	token;
	t_ae_token	content;

	if (((t_ae_token *)elem->content)->type == INCR
			|| ((t_ae_token *)elem->content)->type == DECR)
		return (NULL);
	ft_bzero(&token, sizeof(t_ae_token));
	content = *(t_ae_token *)elem->content;
	token.type = content.type;
	token.value = content.value;
	token.num_value = content.num_value;
	return (ft_lstnew(&token, sizeof(t_ae_token)));
}

void		del_ae_token(void *content, size_t content_size)
{
	t_ae_token *content_t;

	content_t = (t_ae_token *)content;
	ft_strdel(&content_t->word);
	free(content_t);
	content_size = 0;
}

int			ae_is_bool(t_list *token_list)
{
	t_list	*tmp;
	int		size_test_list;

	tmp = token_list;
	size_test_list = 0;
	while (tmp)
	{
		if (((t_ae_token *)tmp->content)->type == COMP
				|| ((t_ae_token *)tmp->content)->type == SEP)
			size_test_list++;
		tmp = tmp->next;
	}
	return (size_test_list);
}

static void	fill_test_list(t_list *token_list, t_list *begin)
{
	t_list		*tmp_token;
	t_list		*tmp_test;
	t_ae_token	*token;
	int			i;

	tmp_token = token_list;
	tmp_test = begin;
	i = -1;
	while (tmp_test && tmp_token && ++i > -1)
	{
		token = (t_ae_token *)tmp_test->content;
		while (tmp_token && ((t_ae_token *)tmp_token->content)->type != COMP
				&& ((t_ae_token *)tmp_token->content)->type != SEP)
			tmp_token = tmp_token->next;
		if (i % 2 == 0)
			token->type = NUM;
		if (i % 2 == 1)
		{
			token->type = ((t_ae_token *)tmp_token->content)->type;
			token->value = ((t_ae_token *)tmp_token->content)->value;
			tmp_token = tmp_token->next;
		}
		tmp_test = tmp_test->next;
	}
}

t_list		*create_test_list(t_list *token_list, int size)
{
	t_list		*begin;
	t_list		*new;
	t_ae_token	token;
	int			i;

	i = -1;
	begin = NULL;
	ft_bzero(&token, sizeof(token));
	while (++i < size)
	{
		if (!(new = ft_lstnew(&token, sizeof(token))))
			continue ;
		if (new && !begin)
			begin = new;
		else
			ft_lstend(&begin, new);
	}
	fill_test_list(token_list, begin);
	return (begin);
}
