/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 17:25:35 by lubenard          #+#    #+#             */
/*   Updated: 2019/12/06 18:36:54 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

/*
** Return true if all process in the job have stopped
** or completed
*/

int job_is_stopped(t_job_lst *jobs)
{
	while (jobs)
	{
		//if (jobs->state == COMPLETED && )
		jobs = jobs->next;
	}
	return (1);
}
