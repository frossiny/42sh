/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42shrc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 03:03:15 by alagroy-          #+#    #+#             */
/*   Updated: 2019/11/27 05:34:40 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <pwd.h>
#include <uuid/uuid.h>
#include <fcntl.h>

static void	error_message(char *join, char *file)
{
	ft_strdel(&join);
	ft_strdel(&file);
	ft_dprintf(2,"Failed to load ~/.42shrc.\n");
}

static void	read_file(int fd)
{
	char	*line;
	int		ret;
	int		tmp;

	tmp = g_shell.able_termcaps;
	(&g_shell)->able_termcaps = 0;
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		eval_exec(&line, 0);
		ft_strdel(&line);
	}
	if (ret == -1)
		ft_dprintf(2, "Failed to load ~/.42shrc\n");
	(&g_shell)->able_termcaps = tmp;
}

void		load_42shrc(void)
{
	char			*join;
	char			*home;
	char			*file;
	struct passwd	*pw;
	int				fd;

	file = ft_strdup("/.42shrc");
	pw = getpwuid(getuid());
	if (!pw || !(home = pw->pw_dir))
		return (error_message(NULL, file));
	join = ft_strjoin(home, file);
	if (!home || !file)
		return (error_message(file, join));
	if ((fd = open(join, O_RDONLY)) == -1)
		return (error_message(file, join));
	read_file(fd);
	ft_strdel(&join);
	ft_strdel(&file);
}
