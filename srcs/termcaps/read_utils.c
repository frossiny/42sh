/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 16:48:58 by vsaltel           #+#    #+#             */
/*   Updated: 2019/11/28 15:33:00 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

int		read_all(int fd, char **dest)
{
	char	buf[BUFF_SIZE];
	char	*str;
	int		ret;

	str = NULL;
	ret = read(fd, buf, BUFF_SIZE - 1);
	if (ret == -1)
		return (ret);
	buf[ret] = '\0';
	*dest = ft_strdup(buf);
	return (ret);
}

void	end_reading(char **dest, char *buf, t_cursor_pos *pos, t_shell *shell)
{
	final_position(pos);
	ft_strdel(&(pos->s_str));
	ft_strdel(&(pos->o_input));
	g_pos.search_mode = 0;
	ft_strdel(&(shell->history.first_command));
	free(buf);
	*dest = pos->str;
}
