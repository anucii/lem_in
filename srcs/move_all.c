/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 19:48:18 by jdaufin           #+#    #+#             */
/*   Updated: 2017/11/01 20:20:57 by jdaufin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

_Bool	has_shortcut(t_list *pathlist)
{
	t_list	*buf[2];
	t_room	*endroom;

	if (!pathlist)
		return (0);
	buf[0] = pathlist;
	buf[1] = get_end();
	if (!((buf[1]) && (endroom = (t_room *)(buf[1]->content))))
		ft_error(PARSING, "Error : no access to endroom", 1);
	buf[1] = NULL;
	while (buf[0])
	{
		if ((buf[1] = (t_list *)buf[0]->content))
		{
			if ((buf[1] = buf[1]->next))
			{
				if (ft_strequ((char *)buf[1]->content, endroom->key))
					return (1);
			}
		}
		buf[0] = buf[0]->next;
	}
	return (0);
}

void	move_all(void)
{
	t_list	*lst;
	t_room	*endroom;
	t_ant	*ant_buf;

	lst = get_end();
	if (!(lst && (endroom = (t_room *)lst->content)))
		ft_error(PARSING, "Error : no access to endroom", 1);
	if (!(lst = ft_antlist(READ, 1)))
		ft_error(PARSING, "Error : no access to antlist", 1);
	while (lst)
	{
		if (lst->content && (ant_buf = (t_ant *)lst->content))
		{
			ant_buf->pos = endroom;
			endroom->is_free = 0;
			ant_buf->display = 1;
			ft_endcount(1);
		}
		lst = lst->next;
	}
}
