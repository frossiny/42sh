/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 16:48:58 by vsaltel           #+#    #+#             */
/*   Updated: 2019/11/27 14:28:55 by vsaltel          ###   ########.fr       */
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
	while ((ret = read(fd, buf, BUFF_SIZE - 1)))
	{
		if (ret == -1)
			break ;
		buf[ret] = '\0';
		if (!str)
			str = ft_strdup(buf);
		else
			str = ft_strfjoin(str, buf, str);
		if (ret < BUFF_SIZE - 1)
			break ;
	}
	*dest = str;
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
