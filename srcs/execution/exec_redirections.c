/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 15:27:23 by frossiny          #+#    #+#             */
/*   Updated: 2020/02/14 15:21:47 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft.h"
#include "execution.h"

static int		redirect_output(t_redirect *redir, int c_only)
{
	int		fd;
	int		otype;

	if (!redir->value)
		return (0);
	otype = O_WRONLY | O_CREAT;
	otype |= (redir->append) ? O_APPEND : O_TRUNC;
	if ((fd = open(redir->value->content, otype, 420)) == -1)
		return (0);
	if (!c_only)
	{
		dup2(fd, redir->filedes);
		close(fd);
	}
	return (1);
}

static void		redirect_input(t_redirect *redir)
{
	int		fd;

	if (!redir->value)
		return ;
	if ((fd = open(redir->value->content, O_RDONLY)) == -1)
		return ;
	dup2(fd, redir->filedes);
	close(fd);
}

static int		handle_aggregate(t_redirect *redir)
{
	if (!redir->value)
		return (0);
	if (redir->type == TOKEN_AGGR)
	{
		if (ft_strequ(redir->value->content, "-"))
			close(redir->filedes);
		else if (ft_isdigit(redir->value->content[0]))
		{
			if (dup2(ft_atoi(redir->value->content), redir->filedes) == -1)
			{
				ft_dprintf(2, "42sh: %s: bad file descriptor\n", \
												redir->value->content);
				return (0);
			}
		}
	}
	return (1);
}

int				handle_redirections(t_redirect *redir, int c_only)
{
	t_redirect	*save;

	save = redir;
	while (redir)
	{
		if (redir->type == TOKEN_REDIRO)
		{
			if (!redirect_output(redir, c_only))
				return (0);
		}
		else if (!c_only && redir->type == TOKEN_REDIRI)
		{
			if (redir->append)
				apply_here_doc(redir);
			else
				redirect_input(redir);
		}
		else if (redir->type == TOKEN_AGGR)
			if (!(handle_aggregate(redir)))
				return (0);
		redir = redir->next;
	}
	return (1);
}
