/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itinerary.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 20:45:47 by jdaufin           #+#    #+#             */
/*   Updated: 2017/10/30 23:51:44 by jdaufin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static _Bool	is_finished(t_list *antlist)
{
	t_room	*endroom;
	t_list 	*buf;
	t_room	*comp;

	if (!antlist)
	{
		ft_error(PARSING, "DBG : no antlist to test", 0);//DBG
		return (0);
	}
	if (!(endroom = (t_room *)(get_end()->content)))
		ft_error(PARSING, "Error : no access to endroom", 1);
	buf = antlist;
	while (buf)
	{
		if (!(buf->content && (comp = ((t_ant *)buf->content)->pos))\
				|| (ft_strcmp(comp->key, endroom->key)))
			return (0);
		buf = buf->next;
	}
	return (1);
}

static _Bool	print_moves(t_list *antlist)
{
	t_list	*buf;
	_Bool	nl;

	if (!antlist)
		ft_error(PARSING,"Error : no list of ants to print", 1);
	buf = antlist;
	nl = 0;
	while (buf)
	{
		if (buf->content && ((t_ant *)buf->content)->display)
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

_Bool			ft_itinerary(t_matches **path_ctrl,	t_list *antlist,\
		t_list *pathlist)
{
	_Bool	print;

	if (!(path_ctrl && *path_ctrl && antlist && pathlist))
		ft_error(PARSING, "Error : missing pointers to solve the map", 1);
	ft_putendl("");
	print = 0;
	while (!is_finished(antlist)) //carefully scrutinize risks of infinite loops
	{
		move_ants(*path_ctrl, antlist, pathlist);
		print |= print_moves(antlist);
	}
	//TODO : free the path_ctrl
	return (print);
}
