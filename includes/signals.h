/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 14:16:18 by vsaltel           #+#    #+#             */
/*   Updated: 2019/12/04 17:14:12 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

#include <signal.h>
#include <stdlib.h>
#include "jobcontrol.h"

void		catch_sigint(int signal);
void		catch_sigquit(int signal);

void		register_signals(void);
void		unregister_signals(void);

typedef struct			s_signals
{
	int		sig;
	void	(*func)();
}						t_signals;

static const t_signals	g_signals[] =
{
	{ 1, NULL },
	{ 2, &catch_sigint },
	{ 3, &catch_sigquit },
	{ 4, NULL },
	{ 5, NULL },
	{ 6, NULL },
	{ 7, NULL },
	{ 8, NULL },
	{ 9, NULL },
	{ 10, NULL },
	{ 11, NULL },
	{ 12, NULL },
	{ 13, SIG_IGN },
	{ 14, NULL },
	{ 15, SIG_IGN },
	{ 16, SIG_IGN },
	{ 17, SIG_IGN },
	{ 18, NULL },
	{ 19, SIG_IGN },
	{ 20, &job_catch_sigchld },
	{ 21, SIG_IGN },
	{ 22, SIG_IGN },
	{ 23, SIG_IGN },
	{ 24, NULL },
	{ 25, NULL },
	{ 26, NULL },
	{ 27, NULL },
	{ 28, SIG_IGN },
	{ 29, SIG_IGN },
	{ 30, NULL },
	{ 31, NULL },
	{ 0, NULL }
};

/*
**	N     SIG			Interatif														Non interactif
**	1     SIGHUP		Quit															Quit
**	2     SIGINT		Stop all actions/relance le prompt (interrupt wait)				Stop all actions
**	3     SIGQUIT
**	4     SIGILL		default	
**	5     SIGTRAP 		default 
**	6     SIGABRT 		default 
**	7     SIGEMT  		default 
**	8     SIGFPE  		default 
**	9     SIGKILL 		default 
**	10    SIGBUS  		default 
**	11    SIGSEGV 		default 
**	12    SIGSYS  		default 
**	13    SIGPIPE		end of file  
**	14    SIGALRM 		default 
**	15    SIGTERM																		Quit
**	16    SIGURG   
**	17    SIGSTOP 		suspend 
**	18    SIGTSTP		ignored if job control
**	19    SIGCONT  
**	20    SIGCHLD  
**	21    SIGTTIN		ignored if job control
**	22    SIGTTOU		ignored if job control
**	23    SIGIO    
**	24    SIGXCPU 		default 
**	25    SIGXFSZ 		default 
**	26    SIGVTALRM		default
**	27    SIGPROF  		default
**	28    SIGWINCH 
**	29    SIGINFO		
**	30    SIGUSR1 		default 
**	31    SIGUSR2 		default 
*/

#endif
