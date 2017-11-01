/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itinerary.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 20:45:47 by jdaufin           #+#    #+#             */
/*   Updated: 2017/11/01 22:18:23 by jdaufin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static _Bool	print_moves(t_list *antlist)
{
	t_list	*buf;
	_Bool	nl;

	if (!antlist)
		ft_error(PARSING, "Error : no list of ants to print", 1);
	buf = antlist;
	nl = 0;
	while (buf)
	{
		if (buf->content && ((t_ant *)buf->content)->display &&\
				((t_ant *)buf->content)->pos->key)
		{
			ft_printf("L%zu-%s ", ((t_ant *)buf->content)->id,\
					((t_ant *)buf->content)->pos->key);
			((t_ant *)buf->content)->display = 0;
			nl = 1;
		}
		buf = buf->next;
	}
	if (nl)
		ft_putendl("");
	return (nl);
}

ssize_t			ft_endcount(_Bool add)
{
	static ssize_t ret = 0;

	return (add ? ++ret : ret);
}

_Bool			ft_itinerary(t_matches **path_ctrl, t_list *antlist, \
		t_list *pathlist)
{
	_Bool	print;
	ssize_t	ant_max;

	if (!(path_ctrl && *path_ctrl && antlist && pathlist))
		ft_error(PARSING, "Error : missing pointers to solve the map", 1);
	ft_putendl("");
	print = 0;
	if ((ant_max = ft_lstlen(antlist)) == -1)
		ft_error(PARSING, "Error : incorrect antlist length", 1);
	while (ft_endcount(0) < ft_lstlen(antlist))
	{
		if (has_shortcut(pathlist))
			move_all();
		else
			move_ants(*path_ctrl, pathlist);
		print |= print_moves(antlist);
	}
	ft_memdel((void **)path_ctrl);
	return (print);
}
