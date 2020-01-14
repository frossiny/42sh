/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 10:40:59 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/14 14:40:06 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include <sys/ioctl.h>
#include "ft_printf.h"
#include "shell.h"
#include "execution.h"

void		sig_ignored(int signal)
{
	(void)signal;
}

void		catch_sigquit(int signal)
{
	(void)signal;
	if (g_shell.current_pipel)
		exec_signal_pipe(g_shell.current_pipel, SIGQUIT);
}

void		catch_sigint(int signal)
{
	(void)signal;
	g_clear_buffer = 1;
	if (g_ignore_signals)
	{
		g_ignore_signals = 0;
		ioctl(0, TIOCSTI, "\4\0");
	}
	else if (g_shell.current_pipel)
		exec_signal_pipe(g_shell.current_pipel, SIGINT);
	else if (!g_child)
	{
		g_return = 1;
		ioctl(0, TIOCSTI, "\n");
	}
}

void		register_signals(void)
{
	int	i;

	i = 0;
	while (g_signals[i].sig)
	{
		if (g_signals[i].func)
			signal(g_signals[i].sig, g_signals[i].func);
		i++;
	}
}

void		unregister_signals(void)
{
	int	i;

	i = 0;
	while (g_signals[i].sig)
	{
		//make exception for job control
		if (g_signals[i].func)
			signal(g_signals[i].sig, SIG_DFL);
		i++;
	}
}
