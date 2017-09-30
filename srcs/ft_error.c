/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 20:28:28 by jdaufin           #+#    #+#             */
/*   Updated: 2017/09/30 21:13:10 by jdaufin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	err_sys(char *msg)
{
	perror(msg);
}

static void	err_parsing(char *msg)
{
	ft_putendl_fd(msg ? msg : "Error", 2);
}

void		ft_error(t_err errtype, char *msg, _Bool stop)
{
	static t_errctrl	*err_array = {{SYSTEM, &err_sys}, {PARSING,\
		&err_parsing}, {NONE, NULL}};
	t_options			*options;
	ssize_t				i;

	i = -1;
	if (!((options = ft_options(NULL))->fail_report))
		ft_putendl_fd("Error", 2);
	else
	{
		while (err_array[++i]->errtype != NONE)
		{
			if (err_array[i]->errtype == errtype)
			{
				(err_array[i]->func)(msg);
				break;
			}
		}
		if (err_array[++i]->errtype == NONE)
			ft_putendl_fd(msg ? msg : "Unknown error", 2);
	}
	if (stop)
		exit(EXIT_FAILURE);
}
