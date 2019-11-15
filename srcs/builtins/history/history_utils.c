/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 16:16:03 by lubenard          #+#    #+#             */
/*   Updated: 2019/11/15 16:13:27 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structs.h"

void	delete_last_elem_hist(t_history *hist)
{
	t_histo_lst *to_delete;

	to_delete = hist->lst;
	hist->lst = hist->lst->next;
	hist->lst->prev = NULL;
	ft_strdel(&to_delete->str);
	free(to_delete);
	hist->size--;
}

void	delete_first_elem_hist(t_history *hist)
{
	t_histo_lst	*to_delete;

	to_delete = hist->first_element;
	hist->first_element = hist->first_element->prev;
	hist->first_element->next = NULL;
	ft_strdel(&to_delete->str);
	free(to_delete);
	hist->size--;
}

void	delete_elem_hist(t_history *hist, t_histo_lst *elem)
{
	elem->prev->next = elem->next;
	elem->next->prev = elem->prev;
	ft_strdel(&elem->str);
	free(elem);
	hist->size--;
}
