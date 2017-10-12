/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_tube.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 18:31:45 by jdaufin           #+#    #+#             */
/*   Updated: 2017/10/12 21:16:28 by jdaufin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static _Bool	key_exists(t_list *lst, char *key)
{
	t_list	*buf;

	if (!(lst && key))
		return (0);
	buf = lst;
	while (buf)
	{
		if (ft_strequ((char *)(buf->content), key))
			return (1);
		buf = buf->next;
	}
	return (0);
}

_Bool	new_tube(char *tgt, char *neighbr)
{
	t_room	*room;
	t_list	*lst;

	if (!(tgt && neighbr))
		return (0);
	if (!(lst = ft_roomlist(READ, tgt)))
		return (0);
	room = (t_room *)lst->content;
	if (!(room->tubes))
		room->tubes = ft_lstnew((void *)neighbr, 1 + ft_strlen(neighbr));
	else
	{
		if (key_exists(room->tubes, neighbr))
			return (0);
		ft_lstadd(&(room->tubes), ft_lstnew((void *)neighbr,\
					1 + ft_strlen(neighbr)));
	}
	return (1);
}

_Bool	add_tube(t_list **rooms, char *line)
{
	char	**slots;

	if (!(rooms && *rooms && line && check_tube(line)))
		return (0);
	if (!(slots = ft_strsplit(line, '-')))
		return (0);
	if (!(ft_roomlist(READ, slots[0]) && (ft_roomlist(READ, slots[1])))\
		|| (!new_tube(slots[0], slots[1]) && !new_tube(slots[1], slots[0])))
		return (0);
	return (1);
}
