/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itinerary.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 20:45:47 by jdaufin           #+#    #+#             */
/*   Updated: 2017/10/26 21:59:38 by jdaufin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static _Bool	is_finished(t_list *antlist)
{
	t_room	*endroom;
	t_list 	*buf;

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
		if (ft_strcmp(((t_ant *)buf->content)->pos->key, endroom->key))
			return (0);
		buf = buf->next;
	}
	return (1);
}

static void		move_ants(t_matches *path_ctrl, t_list *roomlist,\
		t_list *antlist, t_list *pathlist)
{
	t_list	*buf[1];
	ssize_t	i;

	if (!())
		ft_error(PARSING, "", 1);
	i = -1;
	buf[0] = pathlist;
	while (++i < )
		buf[0] = buf[0]->next;
	buf[] = antlist;
	while (buf[] && )
	{
		buf[] = buf[]->next;
	}
}

static _Bool	print_moves(t_list *antlist)
{
	t_list	*buf;
	_Bool	nl;

	if (!antlist)
		ft_error(PARSING,"Error : no list of ants to print" ,1);
	buf = antlist;
	nl = 0;
	while (buf)
	{
		if (buf->content && ((t_ant *)buf->content)->display)
		{
			ft_printf("L%zu-%s ", ((t_ant *)buf->content)->id,\
					((t_ant *)buf->content)->pos->key);
			nl = 1;
		}
		buf = buf->next;
	}
	if (nl)
		ft_putendl("");
	return (nl);
}

_Bool			ft_initinerary(t_matches *path_ctrl, t_list *roomlist,\
		t_list *antlist, t_list *pathlist)
{
	_Bool	print;

	if (!(path_ctrl && roomlist && antlist && pathlist))
		ft_error(PARSING, "Error : missing pointers to solve the map", 1);
	ft_putendl("");
	print = 0;
	while (!is_finished(antlist)) //carefully scrutinize risks of infinite loops
	{
		move_ants(path_ctrl, roomlist, antlist, pathlist);
		print |= print_moves(antlist);
	}
	return (print);
}