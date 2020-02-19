/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 12:19:22 by vsaltel           #+#    #+#             */
/*   Updated: 2020/02/19 16:52:53 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "history.h"

int					is_in_bracket(char *str, int i)
{
	int tmp;

	tmp = i;
	while (i-- > -1)
	{
		if (str[i] == '[' && !is_escaped(str, i, 0))
			break ;
	}
	if (i == -1)
		return (0);
	i = tmp;
	while (str[i])
	{
		if (str[i] == ']' && !is_escaped(str, i, 0))
			break ;
		i++;
	}
	return (str[i] > 0);
}

void				free_history(t_history *history)
{
	t_histo_lst	*curr;
	t_histo_lst	*tmp;

	if (!history || !history->lst)
		return ;
	curr = history->lst;
	while (curr)
	{
		free(curr->str);
		tmp = curr;
		curr = curr->next;
		free(tmp);
	}
	if (history->first_command)
		free(history->first_command);
}

void				memset_history(t_history *history)
{
	history->first_command = NULL;
	history->pos = 0;
}

t_histo_lst			*new_link(char *str)
{
	t_histo_lst			*item;

	if (!(item = malloc(sizeof(t_histo_lst))))
		return (NULL);
	item->str = str;
	item->index = 1;
	item->len = ft_strlen(str);
	item->next = NULL;
	item->prev = NULL;
	return (item);
}
