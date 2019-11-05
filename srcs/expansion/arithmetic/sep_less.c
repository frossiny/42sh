/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sep_less.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 15:57:32 by alagroy-          #+#    #+#             */
/*   Updated: 2019/11/05 17:38:51 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arithmetic.h"

long	ae_lesseq(long a, long b)
{
	if (a <= b)
		return (1);
	return (0);
}

long	ae_or(long a, long b)
{
	if (a || b)
		return (1);
	return (0);
}

long	ae_and(long a, long b)
{
	if (a && b)
		return (1);
	return (0);
}

void	remove_or(t_list *mem_right)
{
	t_list	*tmp1;
	t_list	*tmp2;

	while (mem_right && mem_right->next
			&& ((t_ae_token *)mem_right->next->content)->value == OR)
	{
		tmp1 = mem_right->next;
		tmp2 = mem_right->next->next;
		mem_right->next = mem_right->next->next->next;
		ft_lstdelone(&tmp1, del_ae_token);
		ft_lstdelone(&tmp2, del_ae_token);
	}
}
