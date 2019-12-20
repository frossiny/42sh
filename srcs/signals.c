/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 10:40:59 by frossiny          #+#    #+#             */
/*   Updated: 2019/12/20 15:59:22 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include <sys/ioctl.h>
#include "ft_printf.h"
#include "shell.h"

void		sig_ignored(int signal)
{
	(void)signal;
}

void		catch_sigquit(int signal)
{
	(void)signal;
	if (g_child > 0)
		ft_printf("\n\033[1;31m[SIGNAL]\033[0m %d quit\n", g_child);
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
	else if (!g_child)
	{
		g_return = 1;
		ioctl(0, TIOCSTI, "\n");
	}
	//Kill process
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
	//signal(SIGINT, catch_sigint);
	//signal(SIGQUIT, catch_sigquit);
}

void		unregister_signals(void)
{
	int	i;

	i = 0;
	while (g_signals[i].sig)
	{
		//make exception for job control
		ft_printf("J'appelle signal[%d]\n", i);
		if (g_signals[i].func)
			signal(g_signals[i].sig, SIG_DFL);
		i++;
	}
	//signal(SIGINT, SIG_DFL);
	//signal(SIGQUIT, SIG_DFL);
}
