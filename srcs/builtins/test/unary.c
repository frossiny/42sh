/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unary.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 16:10:39 by pcharrie          #+#    #+#             */
/*   Updated: 2019/11/02 17:03:11 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "utils.h"
#include "shell.h"
#include "libft.h"
#include "variables.h"
#include "builtins.h"
#include "opt.h"

static int	ft_strequstrs(char *str, char *strs[])
{
	int i;

	i = 0;
	while (strs[i])
		if (ft_strequ(str, strs[i++]))
			return (1);
	return (0);
}

char		*g_test_unary_operators[] =
{
	"-b", "-c", "-d", "-e", "-f", "-g", "-h", "-L", "-n", "-p",
	"-r", "-S", "-s", "-u", "-w", "-x", "-z", "!"
};

int			test_unary(t_cmd *c)
{
	struct stat	buf;

	if (!ft_strequstrs(c->args[1], g_test_unary_operators))
		ft_dprintf(2, "42sh: test: %s: unary operator expected\n", c->args[1]);
	else if (stat(c->args[2], &buf)
		&& ((ft_strequ(c->args[1], "-b") && S_ISBLK(buf.st_mode))
		|| (ft_strequ(c->args[1], "-c") && S_ISCHR(buf.st_mode))
		|| (ft_strequ(c->args[1], "-d") && S_ISDIR(buf.st_mode))
		|| ft_strequ(c->args[1], "-e")
		|| (ft_strequ(c->args[1], "-f") && S_ISREG(buf.st_mode))
		|| (ft_strequ(c->args[1], "-g") && (buf.st_mode & S_ISGID))
		|| ((ft_strequ(c->args[1], "-h") || ft_strequ(c->args[1], "-L"))
			&& S_ISLNK(buf.st_mode))
		|| (ft_strequ(c->args[1], "-n") && ft_strlen(c->args[2]))
		|| (ft_strequ(c->args[1], "-p") && S_ISFIFO(buf.st_mode))
		|| (ft_strequ(c->args[1], "-r") && access(c->args[2], R_OK))
		|| (ft_strequ(c->args[1], "-S") && S_ISSOCK(buf.st_mode))
		|| (ft_strequ(c->args[1], "-s") && buf.st_size > 0)
		|| (ft_strequ(c->args[1], "-u") && (buf.st_mode & S_ISUID))
		|| (ft_strequ(c->args[1], "-w") && access(c->args[2], W_OK))
		|| (ft_strequ(c->args[1], "-x") && access(c->args[2], X_OK))
		|| ((ft_strequ(c->args[1], "-z") || ft_strequ(c->args[1], "!"))
			&& !ft_strlen(c->args[2]))))
		return (1);
	return (0);
}
