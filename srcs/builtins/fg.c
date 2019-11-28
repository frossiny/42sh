/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 16:51:40 by lubenard          #+#    #+#             */
/*   Updated: 2019/11/28 12:21:13 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "builtins.h"
#include "jobcontrol.h"
#include "libft.h"


int		b_fg(t_cmd *cmd, t_shell *shell)
{
	(void)cmd;
	if (!shell->jobs.lst)
		ft_putendl_fd("42sh: fg: current: no such job", 2);

	return (0);
}
