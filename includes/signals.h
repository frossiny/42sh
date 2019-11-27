/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 14:16:18 by vsaltel           #+#    #+#             */
/*   Updated: 2019/11/27 18:37:27 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>

void		catch_sigint(int signal);
void		catch_sigquit(int signal);

void		sig_ignored(int signal);
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
	{ 13, &sig_ignored },
	{ 14, NULL },
	{ 15, &sig_ignored },
	{ 16, &sig_ignored },
	{ 17, &sig_ignored },
	{ 18, &sig_ignored },
	{ 19, &sig_ignored },
	{ 20, &sig_ignored },
	{ 21, &sig_ignored },
	{ 22, &sig_ignored },
	{ 23, &sig_ignored },
	{ 24, NULL },
	{ 25, NULL },
	{ 26, NULL },
	{ 27, NULL },
	{ 28, &sig_ignored },
	{ 29, &sig_ignored },
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
