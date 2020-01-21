/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disp_compl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:58:23 by alagroy-          #+#    #+#             */
/*   Updated: 2020/01/21 17:44:21 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"

static int	find_max_len(t_list *compl_list)
{
	int		max;

	max = 0;
	while (compl_list)
	{
		if ((int)ft_strlen(compl_list->content) > max)
			max = ft_strlen(compl_list->content);
		compl_list = compl_list->next;
	}
	return (max);
}

static void	print_compl_list(t_list *compl_list, int win_w)
{
	int		max_len;
	int		nb_col;
	int		i;

	ft_putchar('\n');
	max_len = find_max_len(compl_list);
	nb_col = win_w / (max_len + 3);
	while (compl_list)
	{
		i = -1;
		while (compl_list && ++i < nb_col)
		{
			ft_printf("%-*s", max_len + 3, compl_list->content);
			compl_list = compl_list->next;
		}
		ft_putchar('\n');
	}
}

static int	compl_shared_part(t_cursor_pos *pos, char **str, t_list *compl_list,
		int len)
{
	int		i;
	t_list	*tmp;
	char	*compl;
	int		cont;

	i = 0;
	cont = 1;
	while (cont)
	{
		i++;
		tmp = compl_list;
		while (tmp && tmp->next)
		{
			if (ft_strncmp((char *)tmp->content, (char *)tmp->next->content, i))
				cont = 0;
			tmp = tmp->next;
		}
	}
	if (i == 1 || i == len + 1 || !(compl =
				ft_strsub((char *)compl_list->content, 0, i - 1)))
		return (0);
	*str = ft_insert_str(*str, ft_strdup(compl + len), pos->x_rel);
	pos->x_rel += ft_strlen(compl) - len;
	ft_strdel(&compl);
	return (1);
}

void		disp_compl(t_cursor_pos *pos, char **str, t_list *compl_list,
		int len)
{
	int				size;
	t_cursor_pos	tmp;

	size = ft_lstsize(compl_list);
	if (size == 1)
	{
		*str = ft_insert_str(*str, ft_strdup((char *)compl_list->content + len),
				pos->x_rel);
		pos->x_rel += ft_strlen((char *)compl_list->content) - len;
	}
	else if (!compl_shared_part(pos, str, compl_list, len))
	{
		print_compl_list(compl_list, pos->x_max);
		if (get_pos(&tmp))
			pos->y_min = tmp.y;
	}
}
