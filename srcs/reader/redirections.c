/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 15:27:23 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/15 15:47:34 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft.h"
#include "shell.h"

static void		redirect_output(t_redirect *redir)
{
	int		fd;
	int		otype;

	otype = O_WRONLY | O_CREAT;
	otype |= (redir->append) ? O_APPEND : O_TRUNC;
	if ((fd = open(redir->value->content, otype, 420)) == -1)
		return ;
	dup2(fd, redir->filedes);
	close(fd);
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
	while (redir && redir->value)
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
		redir = redir->next;
	}
	return (1);
}

int				handle_redirections(t_redirect *redir)
{
	t_redirect	*save;

	save = redir;
	while (redir && redir->value)
	{
		if (redir->type == TOKEN_REDIRO)
		{
			redirect_output(redir);
		}
		else if (redir->type == TOKEN_REDIRI)
		{
			if (redir->append)
				apply_here_doc(redir);
			else
				redirect_input(redir);
		}
		redir = redir->next;
	}
	if (!handle_aggregate(save))
		return (0);
	return (1);
}
