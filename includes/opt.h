/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 14:38:25 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/17 14:29:55 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPT_H
# define OPT_H

# include "structs.h"

/*
** Functions
*/

t_options	*opt_parse(t_cmd *cmd, char *optstring, char *bname);
t_opt		*opt_add(t_options *opts, char *name, char *value);
t_opt		*opt_get(t_options *options, char *name);
void		opt_free(t_options *options);

#endif
