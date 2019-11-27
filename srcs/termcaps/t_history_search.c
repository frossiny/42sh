/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_history_search.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 12:28:48 by vsaltel           #+#    #+#             */
/*   Updated: 2019/11/27 16:17:35 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "libft.h"
#include "shell.h"

void		history_search_replace(char **str, char *buf, t_cursor_pos *pos
		, t_history *histo)
{
	t_histo_lst	*curr;
	char		*tmp;
	int			i;

	if (buf && (pos->search_mode = 1))
		pos->s_str = !pos->s_str ? ft_strdup(buf) :
			ft_strfjoin(pos->s_str, buf, pos->s_str);
	pos->x_rel = 0;
	if (ft_strlen(pos->s_str))
	{
		curr = histo->lst;
		i = 0;
		while (curr && i < pos->search_mode)
		{
			if ((tmp = ft_strstr(curr->str, pos->s_str)))
			{
				i++;
				ft_strdel(str);
				*str = ft_strdup(curr->str);
				pos->x_rel = tmp - curr->str;
			}
			curr = curr->next;
		}
	}
}

void		history_search_delete(char **str, t_cursor_pos *pos,
													t_history *histo)
{
	int		len;
	char	*tmp;

	if (!pos->s_str)
		return ;
	len = ft_strlen(pos->s_str);
	if (len)
	{
		tmp = pos->s_str;
		pos->s_str = ft_strndup(pos->s_str, len - 1);
		free(tmp);
		history_search_replace(str, NULL, pos, histo);
	}
	else
	{
		ft_strdel(&pos->s_str);
		ft_strdel(str);
		pos->search_mode = 0;
		pos->x_rel = 0;
	}
}

void		termcaps_history_search(char **str, t_cursor_pos *pos
		, t_shell *shell)
{
	(void)shell;
	if (pos->visual_mode)
		return ;
	if (pos->search_mode)
	{
		pos->search_mode++;
		history_search_replace(str, NULL, pos, &shell->history);
	}
	else
	{
		pos->s_str = ft_strdup("");
		pos->search_mode = 1;
	}
}
