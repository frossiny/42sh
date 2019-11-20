/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 10:40:59 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/20 14:34:22 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <sys/ioctl.h>
#include "ft_printf.h"
#include "shell.h"

/*
**	N     SIG			Interatif														Non interactif
**	1     SIGHUP		Quit															Quit
**	2     SIGINT		Stop all actions/relance le prompt (interrupt wait)				Stop all actions
**	3     SIGQUIT
**	4     SIGILL	
**	5     SIGTRAP  
**	6     SIGABRT  
**	7     SIGEMT   
**	8     SIGFPE   
**	9     SIGKILL  
**	10    SIGBUS   
**	11    SIGSEGV  
**	12    SIGSYS   
**	13    SIGPIPE  
**	14    SIGALRM  
**	15    SIGTERM																		Quit
**	16    SIGURG   
**	17    SIGSTOP  
**	18    SIGTSTP		ignored 
**	19    SIGCONT  
**	20    SIGCHLD  
**	21    SIGTTIN		ignored 
**	22    SIGTTOU		ignored 
**	23    SIGIO    
**	24    SIGXCPU  
**	25    SIGXFSZ  
**	26    SIGVTALRM
**	27    SIGPROF  
**	28    SIGWINCH 
**	29    SIGINFO  
**	30    SIGUSR1  
**	31    SIGUSR2  
*/
static void	catch_sigquit(int signal)
{
	(void)signal;
	if (g_child > 0)
		ft_printf("\n\033[1;31m[SIGNAL]\033[0m %d quit\n", g_child);
}

static void	catch_sigint(int signal)
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
}

void		register_signals(void)
{
	signal(SIGINT, catch_sigint);
	signal(SIGQUIT, catch_sigquit);
}

void		unregister_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
