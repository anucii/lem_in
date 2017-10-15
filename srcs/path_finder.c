/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/13 19:53:51 by jdaufin           #+#    #+#             */
/*   Updated: 2017/10/15 11:51:05 by jdaufin          ###   ########.fr       */
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

static t_list	*ctrl_list(char *elmt)
{
	static t_list	*ctrl = NULL;
	t_list			*new;

	if (!elmt)
		return (NULL);
	if (ft_strequ(elmt, "htkc-2#0"))
	{
		ft_lstdel(&ctrl, &ft_linkdel);
		return (NULL);
	}
	if (!ctrl)
	{
		if (!(ctrl = ft_lstnew((void *)elmt, 1 + ft_strlen(elmt))))
			ft_error(SYSTEM,\
					"Error in control list of weight setting precedence", 1);
	}
	else
	{
		if (!(new = ft_lstnew((void *)elmt, 1 + ft_strlen(elmt))))
			ft_error(SYSTEM,\
					"Error in control list of weight setting precedence", 1);
		ft_lstappend(&ctrl, new);
	}
	return (ctrl);
}

short	get_weight(t_room **room, t_list *parents)
{
	t_list	*mates;
	t_list	*lst;
	//	t_room	*neighbour;
	short	cand;

	if (!(room && *room && (mates = (*room)->tubes)))
		return (SHRT_MIN);
	if ((*room)->status == END)
	{
		(*room)->weight = 0;
		return (0);
	}
	while (mates)
	{
		if ((*room)->status == START)
			ctrl_list((*room)->key);
		if ((lst = ft_roomlist(READ, (char *)(mates->content))))
		{
			if (!is_parent((/*neighbour = */(t_room *)(lst->content))->key,\
						parents))
			{
				cand = 1 + get_weight(/*&neighbour*/(t_room **)&(lst->content),\
						ctrl_list((char *)mates->content));
				(*room)->weight = cand < (*room)->weight ? cand :\
								  (*room)->weight;
			}
		}
		mates = mates->next;
		if ((*room)->status == START)
			ctrl_list("htkc-2#0");
		//ctrl_list("htkc-2#0");
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
