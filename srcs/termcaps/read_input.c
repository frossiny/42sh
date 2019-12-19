/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 19:12:36 by vsaltel           #+#    #+#             */
/*   Updated: 2019/12/19 15:47:06 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <curses.h>
#include <term.h>
#include <termios.h>
#include "get_next_line.h"
#include "jobcontrol.h"
#include "shell.h"

static void	new_entry(char **str, char *buf, t_cursor_pos *pos
		, t_history *histo)
{
	histo->pos = 0;
	pos->compl = 0;
	if (pos->search_mode)
	{
		history_search_replace(str, buf, pos, histo);
		return (reprint(*str, pos, pos->x_rel, 0));
	}
	else if (!*str)
		*str = ft_strdup(buf);
	else if (pos->visual_mode)
	{
		visual_replace(str, buf, pos);
		return (reprint(*str, pos, pos->x_rel, 0));
	}
	else if ((*str)[pos->x_rel])
		*str = ft_strjoinf(ft_strndup(*str, pos->x_rel),
				ft_strfjoin(buf, *str + pos->x_rel, *str));
	else
		*str = ft_strfjoin(*str, buf, *str);
	reprint(*str, pos, pos->x_rel + ft_strlen(buf), 0);
}

static int	check_input(char *buf, char **str, t_cursor_pos *pos
		, t_shell *shell)
{
	if (ft_strequ(buf, "\004") && (!str || !(*str) || ft_strequ(*str, "")))
	{
		free(buf);
		ft_strdel(&(shell->history.first_command));
		ft_strdel(&(pos->s_str));
		ft_strdel(str);
		return (0);
	}
	if (g_clear_buffer)
	{
		free(buf);
		ft_strdel(str);
		ft_strdel(&(pos->s_str));
		ft_strdel(&(shell->history.first_command));
		g_return = 1;
		final_position(pos);
		return (1);
	}
	return (2);
}

static int	termcaps_gnl(int fd, char **dest, t_shell *shell)
{
	int				ret;
	char			*buf;

	while ((ret = read_all(fd, &buf)))
	{
		if (!g_pos.str)
			g_pos.str = ft_strdup("");
		if (ret == -1
			|| (ret = check_input(buf, &(g_pos.str), &g_pos, shell)) <= 1)
			return (ret);
		if (buf[0] == '\n')
			break ;
		if (is_special(buf))
			execute_termcaps(buf, &(g_pos.str), &g_pos, shell);
		else
			new_entry(&(g_pos.str), buf, &g_pos, &(shell->history));
		free(buf);
	}
	end_reading(dest, buf, &g_pos, shell);
	return (ret > 0 ? 1 : ret);
}

int			get_input(int fd, char **dest, t_shell *shell)
{
	int				ret;

	job_check_status();
	g_clear_buffer = 0;
	*dest = NULL;
	if (shell->able_termcaps)
	{
		memset_all(&(g_pos.str), &(shell->history), &g_pos);
		signal(SIGWINCH, &resize);
		ret = termcaps_gnl(fd, dest, shell);
		signal(SIGWINCH, SIG_DFL);
	}
	else
	{
		ret = get_next_line(fd, dest);
		if (g_clear_buffer)
		{
			ft_strdel(dest);
			g_clear_buffer = 0;
		}
	}
	return (ret);
}
