/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 11:24:47 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/28 11:35:09 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "ast.h"
#include <fcntl.h>

void		apply_here_doc(t_redirect *redir)
{
	int		fd;
	int		i;

	i = -1;
	if ((fd = open("/tmp/heredoc42sh", O_CREAT | O_TRUNC | O_WRONLY, 0755))
			== -1)
		return ;
	while (redir->heredoc && redir->heredoc[++i])
		ft_putendl_fd(redir->heredoc[i], fd);
	close(fd);
	if ((fd = open("/tmp/heredoc42sh", O_RDONLY)) == -1)
		return ;
	dup2(fd, STDIN_FILENO);
	unlink("/tmp/heredoc42sh");
	close(fd);
}
