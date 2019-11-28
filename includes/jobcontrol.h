/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobcontrol.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 14:08:11 by lubenard          #+#    #+#             */
/*   Updated: 2019/11/28 10:56:25 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOBCONTROL_H
# define JOBCONTROL_H

# include "structs.h"

/*
** If needed, you can remove shell var from proto and use global instead
*/

t_jobs_lst	*job_new(t_cmd *cmd);
void		job_delete(t_shell *shell, size_t pid);
void		job_destroy_all(t_shell *shell);
void		job_check_status(void);
char		*job_get_command(t_cmd *cmd);

#endif
