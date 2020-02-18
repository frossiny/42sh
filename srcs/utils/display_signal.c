/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 14:13:07 by vsaltel           #+#    #+#             */
/*   Updated: 2020/02/14 13:36:13 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "shell.h"

const static char	*g_signals_desc[] =
{
	"",
	"terminal line hangup",
	"interrupt",
	"quit",
	"illegal instruction",
	"trace trap",
	"abort",
	"emulate instruction executed",
	"floating-point exception",
	"kill",
	"bus error",
	"segmentation violation",
	"non-existent system call invoked",
	"write on a pipe with no reader",
	"real-time timer expired",
	"software termination signal",
	"urgent condition present on socket",
	"stop",
	"stop signal generated from keyboard",
	"continue after stop",
	"child status has changed",
	"background read attempted from control terminal",
	"background write attempted to control terminal",
	"I/O is possible on a descriptor",
	"cpu time limit exceeded",
	"file size limit exceeded",
	"virtual time alarm",
	"profiling timer alarm",
	"Window size change",
	"status request from keyboard",
	"User defined signal 1",
	"User defined signal 2"
};

int					display_signal(int sigid)
{
	if (sigid > 0 && sigid <= 31 && sigid != SIGPIPE && sigid != SIGINT)
		ft_printf("\n\033[1;31m[SIGNAL]\033[0m %d %s",
			sigid, g_signals_desc[sigid]);
	return (128 + sigid);
}
