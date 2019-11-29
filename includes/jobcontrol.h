/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobcontrol.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 14:08:11 by lubenard          #+#    #+#             */
/*   Updated: 2019/11/29 11:43:02 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOBCONTROL_H
# define JOBCONTROL_H

# include "structs.h"

/*
** If needed, you can remove shell var from proto and use global instead
*/

t_jobs_lst	*job_new(t_cmd *cmd, int pid);
t_jobs_lst	*job_new_pipe(t_pipel *pline, t_childs *childs);
void		job_free(t_jobs_lst *job);
void		job_delete(t_shell *shell, int pid);
void		jobs_destroy_all(t_shell *shell);
void		job_check_status(void);
t_jobs_lst	*job_search(t_shell *shell, int job_number);
char		*job_get_command(t_cmd *cmd);
char		*job_get_pipe_command(t_pipel *pline);
int			job_can_exit(void);

#endif
