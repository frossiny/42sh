/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 14:43:27 by alagroy-          #+#    #+#             */
/*   Updated: 2019/11/05 18:05:12 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arithmetic.h"

long		(*g_comp_router[8])(long, long) =\
{
	ae_equ,
	ae_nequ,
	ae_great,
	ae_greateq,
	ae_less,
	ae_lesseq,
	ae_and,
	ae_or,
};

static long	exec_op(t_list *mem_left, t_list *op, t_list *mem_right)
{
	t_ae_value	op_id;
	long		value;

	op_id = ((t_ae_token *)op->content)->value;
	if (op_id < EQU)
		return (0);
	value = g_comp_router[op_id - EQU](
			((t_ae_token *)mem_left->content)->num_value,
			((t_ae_token *)mem_right->content)->num_value);
	if (op_id == OR && value == 1)
		remove_or(mem_right);
	return (value);
}

static int	fill_members(t_list *test_list, t_list **mem_left,
		t_list **mem_right, t_list **op)
{
	t_list	*tmp;

	tmp = test_list;
	while (tmp && tmp != *op)
	{
		if (((t_ae_token *)tmp->content)->type == NUM)
			*mem_left = tmp;
		tmp = tmp->next;
	}
	*mem_right = (*op)->next;
	if (!*mem_left || !*mem_right)
		return (0);
	return (1);
}

static int	fill_op(t_list *test_list, t_list **op)
{
	t_list *tmp;

	tmp = test_list;
	while (tmp)
	{
		if (((t_ae_token *)tmp->content)->value == AND)
		{
			*op = tmp;
			break ;
		}
		tmp = tmp->next;
	}
	if (*op)
		return (1);
	return (0);
}

static int	fill_elems(t_list *test_list, t_list **mem_left, t_list **mem_right,
		t_list **op)
{
	t_list	*tmp;

	tmp = test_list;
	while (tmp)
	{
		if (((t_ae_token *)tmp->content)->type == COMP)
		{
			*op = tmp;
			break ;
		}
		tmp = tmp->next;
	}
	tmp = test_list;
	if (!*op)
		while (tmp)
		{
			if (((t_ae_token *)tmp->content)->value == OR)
			{
				*op = tmp;
				break ;
			}
			tmp = tmp->next;
		}
	if (!*op)
		if (!fill_op(test_list, op))
			return (0);
	return (fill_members(test_list, mem_left, mem_right, op));
}

long		eval_test(t_list *test_list)
{
	t_list	*mem_left;
	t_list	*mem_right;
	t_list	*op;
	long	value;

	mem_left = NULL;
	mem_right = NULL;
	op = NULL;
	value = 0;
	while (fill_elems(test_list, &mem_left, &mem_right, &op))
	{
		((t_ae_token *)mem_left->content)->num_value = exec_op(mem_left, op,
			mem_right);
		mem_left->next = mem_right->next;
		ft_lstdelone(&op, del_ae_token);
		ft_lstdelone(&mem_right, del_ae_token);
		value = ((t_ae_token *)mem_left->content)->num_value;
	}
	return (value);
}
