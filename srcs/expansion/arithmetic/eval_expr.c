/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_expr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 19:49:31 by alagroy-          #+#    #+#             */
/*   Updated: 2019/11/05 00:28:20 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arithmetic.h"

long		(*g_op_router[7])(long, long) =\
{
	ae_sum,
	NULL,
	ae_sub,
	NULL,
	ae_mult,
	ae_div,
	ae_mod,
};

static long	exec_op(t_list *mem_left, t_list *op, t_list *mem_right)
{
	t_ae_value	op_id;

	op_id = ((t_ae_token *)op->content)->value;
	if (op_id > MOD || op_id == PPLUS || op_id == MMINUS || !mem_left
			|| !mem_right)
		return (0);
	return (g_op_router[op_id](((t_ae_token *)mem_left->content)->num_value,
				((t_ae_token *)mem_right->content)->num_value));
}

static int	fill_member(t_list *token_list, t_list **mem_left,
		t_list **mem_right, t_list **op)
{
	t_list	*tmp;

	tmp = token_list;
	while (tmp && tmp != *op)
	{
		if (((t_ae_token *)tmp->content)->type == NUM
				|| ((t_ae_token *)tmp->content)->type == WORD)
			*mem_left = tmp;
		tmp = tmp->next;
	}
	while (tmp)
	{
		if (((t_ae_token *)tmp->content)->type == NUM
				|| ((t_ae_token *)tmp->content)->type == WORD)
		{
			*mem_right = tmp;
			break ;
		}
		tmp = tmp->next;
	}
	if (!*mem_left || !*mem_right)
		return (0);
	return (1);
}

static int	fill_elems(t_list *token_list, t_list **mem_left,
		t_list **mem_right, t_list **op)
{
	t_list	*tmp;

	tmp = token_list;
	while (tmp)
	{
		if (((t_ae_token *)tmp->content)->value >= MULT
				&& ((t_ae_token *)tmp->content)->value <= MOD)
		{
			*op = tmp;
			break ;
		}
		tmp = tmp->next;
	}
	tmp = token_list;
	if (!*op)
		while (tmp)
		{
			if (((t_ae_token *)tmp->content)->type == OPERATOR
					&& (((t_ae_token *)tmp->content)->value == PLUS
					 || ((t_ae_token *)tmp->content)->value == MINUS))
			{
				*op = tmp;
				break ;
			}
			tmp = tmp->next;
		}
	return (!*op ? 0 : fill_member(token_list, mem_left, mem_right, op));
}

long	eval_expr(t_list *expr)
{
	t_list	*mem_left;
	t_list	*mem_right;
	t_list	*op;
	long	value;

	mem_left = NULL;
	mem_right = NULL;
	op = NULL;
	value = ((t_ae_token *)expr->content)->num_value;
	while (fill_elems(expr, &mem_left, &mem_right, &op))
	{
		((t_ae_token *)mem_left->content)->num_value = exec_op(mem_left,
			op, mem_right);
		mem_left->next = mem_right->next;
		ft_lstdelone(&op, del_ae_token);
		ft_lstdelone(&mem_right, del_ae_token);
		value = ((t_ae_token *)mem_left->content)->num_value;
	}
	return (value);
}
