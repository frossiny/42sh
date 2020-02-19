/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_visual_paste.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 16:07:35 by vsaltel           #+#    #+#             */
/*   Updated: 2019/08/12 18:42:09 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

void		visual_replace(char **str, char *buf, t_cursor_pos *pos)
{
	char	*l;
	char	*r;

	pos->visual_mode = 0;
	if (pos->v_beg < pos->x_rel)
	{
		l = ft_strndup(*str, pos->v_beg);
		if ((*str)[pos->x_rel] != '\0')
			r = ft_strdup(*str + pos->x_rel + 1);
		else
			r = ft_strdup("");
	}
	else
	{
		l = ft_strndup(*str, pos->x_rel);
		if ((*str)[pos->v_beg] != '\0')
			r = ft_strdup(*str + pos->v_beg + 1);
		else
			r = ft_strdup("");
	}
	free(*str);
	*str = ft_strjoint(l, buf, r);
	ft_multifree(&l, &r, NULL);
	pos->x_rel = pos->v_beg < pos->x_rel ?
		pos->v_beg + ft_strlen(buf) : pos->x_rel + ft_strlen(buf);
}

void		termcaps_visual_paste(char **str, t_cursor_pos *pos, t_shell *shell)
{
	char	*tmp;

	(void)shell;
	if (!pos->v_str || !str)
		return ;
	if (!pos->visual_mode)
	{
		if (*str)
		{
			tmp = ft_strndup(*str, pos->x_rel);
			tmp = ft_strfjoin(tmp, pos->v_str, tmp);
			*str = ft_strfjoin(tmp, *str + pos->x_rel, *str);
			free(tmp);
			pos->x_rel = pos->x_rel + ft_strlen(pos->v_str);
		}
		else
		{
			*str = ft_strdup(pos->v_str);
			pos->x_rel = ft_strlen(pos->v_str);
		}
	}
	else
		visual_replace(str, pos->v_str, pos);
}
