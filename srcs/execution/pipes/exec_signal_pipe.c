/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_signal_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 15:00:17 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/14 14:39:19 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "execution.h"

void	exec_signal_pipe(t_pipel *pipeline, int signal)
{
	if (signal < 0 || signal > 31)
		return ;
	while (pipeline)
	{
		kill(pipeline->pid, signal);
		pipeline = pipeline->next;
	}
}
