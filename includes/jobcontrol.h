/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobcontrol.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 14:08:11 by lubenard          #+#    #+#             */
/*   Updated: 2019/11/27 17:46:54 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOBCONTROL_H
# define JOBCONTROL_H
#include "shell.h"

/*
** If needed, you cam remove shell var from proto and use global instead
*/

t_jobs	*job_new(void);
void	job_delete(t_shell *shell, size_t pid);
void	job_destroy_all(t_shell *shell);
void	job_check_status(void);

#endif
