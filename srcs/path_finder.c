/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/13 19:53:51 by jdaufin           #+#    #+#             */
/*   Updated: 2017/10/14 17:26:47 by jdaufin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static _Bool	is_parent(char *key, t_list *parents)
{
	t_list	*buf;

	if (!(parents && key))
		return (0);
	buf = parents;
	while (buf)
	{
		if (ft_strequ((char *)(buf->content), key))
			return (1);
		buf = buf->next;
	}
	return (0);
}

short	get_weight(t_room **room, t_list **parents)
{
	t_list	*mates;
	t_list	*lst[2];
	t_room	*neighbour;
	short	cand;

	if (!(room && *room && (mates = (*room)->tubes)))
		return (SHRT_MIN);
	if ((*room)->status == END)
	{
		(*room)->weight = 0;
		ft_lstdel(parents, &ft_linkdel);
		return (0);
	}
	if (! (lst[0] = (parents && *parents) ? NULL : ft_lstnew((void *)\
					(*room)->key, 1 + ft_strlen((char *)((*room)->key)))))
		ft_lstappend(parents, ft_lstnew((void *)(*room)->key, 1\
					+ ft_strlen((char *)(*room)->key)));
	while (mates)
	{
		if ((lst[1] = ft_roomlist(READ, (char *)(mates->content))))
		{
			if (!is_parent((neighbour = (t_room *)lst[1]->content)->key,\
						lst[0] ? lst[0] : *parents))
			{
				cand = 1 + get_weight(&neighbour, parents && *parents ? parents :\
						&lst[0]);
				(*room)->weight = cand < (*room)->weight ? cand :\
								  (*room)->weight;
			}
		}
		mates = mates->next;
	}
	return ((*room)->weight);
}

_Bool	set_weights(void)
{
	t_list	*roomlist;
	t_room	*cur;

	if (!(roomlist = ft_roomlist(READ, NULL)))
		return (0);
	while (roomlist && ((cur = (t_room *)roomlist->content)->status != START))
		roomlist = roomlist->next;
	return (get_weight(&cur, NULL) < 0 ? 0 : 1);
}
