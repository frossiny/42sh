/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 14:31:38 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/16 16:49:12 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "opt.h"

static int	parse_mul(t_options *opts, char *opt, const char *optstring, const char *bname)
{
	char	*tmp;
	size_t i;

	i = 0;
	while (opt[++i])
	{
		if (ft_strchr(optstring, opt[i]))
		{
			tmp = ft_strsub(opt, i, 1);
			if (!opt_get(opts, tmp))
				opt_add(opts, tmp, NULL);
			free(tmp);
		}
		else
		{
			ft_printf("%s: illegal option -- %c\n", bname, opt[i]);
			opts->ret = -1;
			return (0);
		}
	}
	return (1);
}

t_options	*opt_parse(int argc, char **argv, const char *optstring, const char *bname)
{
	t_options	*options;
	char		*find;

	if (!(options = (t_options *)malloc(sizeof(t_options))))
		return (NULL);
	options->opts = NULL;
	options->ret = 0;
	options->last = 0;
	argv++;
	while (--argc)
	{
		if ((*argv)[0] != '-' || ft_strnequ("--", *argv, 2))
			break ;
		if (ft_strlen(*argv) > 2)
		{
			if (!parse_mul(options, *argv, optstring, bname))
				return (options);
		}
		else
		{
			if ((find = ft_strchr(optstring, (*argv)[1])))
			{
				if (find[1] == ':')
				{
					if (argc == 1)
					{
						ft_printf("%s: option requires an argument -- %c\n", bname, (*argv)[1]);
						options->ret = -2;
						return (options);
					}
					if (!opt_get(options, (*argv) + 1))
						opt_add(options, (*argv) + 1, argv[1]);
					argv++;
					argc--;
				}
				else if (!opt_get(options, (*argv) + 1))
					opt_add(options, (*argv) + 1, NULL);
			}
			else
			{
				ft_printf("%s: illegal option -- %c\n", bname, (*argv)[1]);
				options->ret = -1;
				return (options);
			}
		}
		argv++;
	}
	return (options);
}
