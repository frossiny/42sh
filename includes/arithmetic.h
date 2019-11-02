/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 18:19:27 by alagroy-          #+#    #+#             */
/*   Updated: 2019/11/02 16:50:49 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARITHMETIC_H
# define ARITHMETIC_H
# include "structs.h"
# include "libft.h"
# define NBR_SYM 12
# define NBR_AE_VAL 15

t_list				*lex_ae_str(char *str);
long				ft_atol(char *str);

#endif
