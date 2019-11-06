/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 17:03:49 by vsaltel           #+#    #+#             */
/*   Updated: 2019/11/06 16:32:15 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALIAS_H
# define ALIAS_H

# include "structs.h"

void		alias_display_all(t_alias *alias);
void		alias_display_one(t_alias *alias, char *key);
int			alias_new(t_alias **alias, char *key, char *value);
t_alias		*alias_get(t_alias *alias, char *key);
void		alias_free_all(t_alias **list);
void		alias_free_one(t_alias *alias);

#endif
