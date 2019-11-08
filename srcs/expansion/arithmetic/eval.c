/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 18:03:04 by alagroy-          #+#    #+#             */
/*   Updated: 2019/11/08 17:15:55 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arithmetic.h"

static long	eval_ae_num(t_list *token_list)
{
	t_list		*tmp;
	t_list		*copy;
	long		result;

	copy = ft_lstmap(token_list, copy_ae_token);
	tmp = copy;
	while (tmp->next && ((t_ae_token *)tmp->next->content)->type != COMP
			&& ((t_ae_token *)tmp->next->content)->type != SEP)
		tmp = tmp->next;
	ft_lstdel(&tmp->next, del_ae_token);
	tmp->next = NULL;
	tmp = copy;
	result = eval_expr(copy);
	ft_lstdel(&copy, del_ae_token);
	return (result);
}

static long	eval_ae_test(t_list *token_list, int size)
{
	t_list	*test_list;
	t_list	*tmp;
	t_list	*tmp_tok;
	long	value;

	size = 2 * size + 1;
	test_list = create_test_list(token_list, size);
	tmp = test_list;
	tmp_tok = token_list;
	while (tmp && tmp_tok)
	{
		((t_ae_token *)tmp->content)->num_value = eval_ae_num(tmp_tok);
		if (tmp->next)
			tmp = tmp->next->next;
		while (tmp_tok && ((t_ae_token *)tmp_tok->content)->type != COMP
				&& ((t_ae_token *)tmp_tok->content)->type != SEP)
			tmp_tok = tmp_tok->next;
		tmp_tok = tmp_tok ? tmp_tok->next : tmp_tok;
	}
	value = eval_test(test_list);
	ft_lstdel(&test_list, del_ae_token);
	return (value);
}

long		eval_ae(t_list *token_list)
{
	long	value;
	int		size;

	size = ae_is_bool(token_list);
	if (size)
		value = eval_ae_test(token_list, size);
	else
		value = eval_ae_num(token_list);
	return (value);
}
