/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 11:02:25 by vsaltel           #+#    #+#             */
/*   Updated: 2019/10/14 18:39:46 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include "libft.h"
#include "shell.h"
#include "termcaps.h"

static const t_ex_caps g_caps_list[] =
{
	{"\e[1;2A", 6, &termcaps_up},
	{"\e[1;2B", 6, &termcaps_down},
	{"\e[1;2C", 6, &termcaps_right_word},
	{"\e[1;2D", 6, &termcaps_left_word},
	{"\e[3~", 4, &termcaps_delete_right},
	{"\e[D", 3, &termcaps_left},
	{"\e[C", 3, &termcaps_right},
	{"\e[A", 3, &termcaps_history_next},
	{"\e[B", 3, &termcaps_history_prev},
	{"\022", 3, &termcaps_history_search},
	{"\e[H", 3, &termcaps_home},
	{"\e[F", 3, &termcaps_end},
	{"\026", 1, &termcaps_visual_mode},
	{"\031", 1, &termcaps_visual_copy},
	{"\030", 1, &termcaps_visual_cut},
	{"\020", 1, &termcaps_visual_paste},
	{"\177", 1, &termcaps_delete},
	{"\011", 1, &termcaps_completion},
	{NULL, 1, NULL}
};

int					is_special(const char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (!ft_isprint(s[i]))
			return (1);
		i++;
	}
	return (0);
}

static t_ex_caps	search_caps(const char *s)
{
	const t_ex_caps	empty = {NULL, 1, NULL};
	size_t			i;

	if (!s)
		return (empty);
	i = 0;
	while (g_caps_list + i && (g_caps_list[i]).content)
	{
		if (ft_strncmp(g_caps_list[i].content, s, g_caps_list[i].size) == 0)
			return (g_caps_list[i]);
		i++;
	}
	tputs(tgetstr("bl", NULL), 1, ft_putchar);
	tputs(tgetstr("vb", NULL), 1, ft_putchar);
	return (empty);
}

int					execute_termcaps(char *buf, char **str
		, t_cursor_pos *pos, t_shell *shell)
{
	t_ex_caps termcaps;

	termcaps = search_caps(buf);
	if (!(termcaps.content))
		return (0);
	if (termcaps.func)
	{
		if (pos->search_mode && ft_strcmp(buf, "\022")
				&& ft_strcmp(buf, "\177"))
		{
			ft_strdel(&pos->s_str);
			pos->search_mode = 0;
		}
		if (!ft_strnequ("\011", termcaps.content, 1))
		{
			pos->compl = 0;
		}
		termcaps.func(str, pos, shell);
		reprint(*str, pos, pos->x_rel);
	}
	return (1);
}
