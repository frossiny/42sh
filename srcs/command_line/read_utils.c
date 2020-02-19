/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 16:48:58 by vsaltel           #+#    #+#             */
/*   Updated: 2020/01/15 18:47:08 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

char	*del_non_ascii_char(char *input)
{
	int		i;
	int		li;
	char	*res;
	char	*tmp;

	i = 0;
	li = 0;
	res = ft_strdup("");
	while (input[i])
	{
		if (input[i] < 0 || input[i] > 127)
		{
			tmp = ft_strsub(input, li, i - li);
			res = ft_strfjoin(res, tmp, res);
			free(tmp);
			while (input[i] && (input[i] < 0 || input[i] > 127))
				i++;
			li = i;
		}
		i++;
	}
	tmp = ft_strsub(input, li, i - li);
	res = ft_strfjoin(res, tmp, res);
	free(tmp);
	return (res);
}

int		read_all(int fd, char **dest)
{
	char	buf[BUFF_SIZE];
	char	*str;
	int		ret;

	str = ft_strdup("");
	while ((ret = read(fd, buf, BUFF_SIZE - 1)))
	{
		if (ret == -1)
			break ;
		buf[ret] = '\0';
		str = ft_strfjoin(str, buf, str);
		if (ret < BUFF_SIZE - 1)
			break ;
	}
	*dest = del_non_ascii_char(str);
	free(str);
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
