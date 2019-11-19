/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobcontrol.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 14:08:11 by lubenard          #+#    #+#             */
/*   Updated: 2019/11/19 19:03:21 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOBCONTROL_H
# define JOBCONTROL_H
#include "shell.h"

/*
** If needed, you cam remove shell var from proto and use global instead
*/

t_jobs	*new_job(t_anode *ast);
void	delete_job(t_shell *shell, size_t pid);
void	destroy_all_jobs(t_shell *shell);

#endif
