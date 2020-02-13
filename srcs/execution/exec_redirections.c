/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 15:27:23 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/30 17:28:40 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft.h"
#include "execution.h"

static void		redirect_output(t_redirect *redir, int c_only)
{
	int		fd;
	int		otype;

	otype = O_WRONLY | O_CREAT;
	otype |= (redir->append) ? O_APPEND : O_TRUNC;
	if ((fd = open(redir->value->content, otype, 420)) == -1)
		return ;
	if (!c_only)
	{
		dup2(fd, redir->filedes);
		close(fd);
	}
}

static void		redirect_input(t_redirect *redir)
{
	int		fd;

	if ((fd = open(redir->value->content, O_RDONLY)) == -1)
		return ;
	dup2(fd, redir->filedes);
	close(fd);
}

static int		handle_aggregate(t_redirect *redir)
{
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
	while (redir && redir->value)
	{
		if (redir->type == TOKEN_REDIRO)
			redirect_output(redir, c_only);
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
