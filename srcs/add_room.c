/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_room.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 17:56:10 by jdaufin           #+#    #+#             */
/*   Updated: 2017/10/11 21:07:43 by jdaufin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	room_init(t_room *ptr, t_flag status)
{
	if (ptr)
		*ptr = (t_room){NULL, 1, status, {0,0}, NULL};
}

_Bool	is_duplicate(t_list *room)
{
	t_list	*buf;
	t_room	*comp;

	if (!(room && (buf = ft_roomlist(READ, "all"))))
		return (0);
	while (buf)
	{
		if ((comp = (t_room *)(buf->content)))
		{
			if (ft_strequ(comp->key, ((t_room *)(room->content))->key))
				return (1);
			if ((comp->coord[0] == ((t_room *)(room->content))->coord[0])\
					&& (comp->coord[1] ==\
						(((t_room *)(room->content))->coord[1])))
				return (1);
		}
		buf = buf->next;
	}
	return (0);
}

t_list	*get_room(char *line, t_flag status)
{
	t_list	*ret;
	t_room	room;
	char	**tab;
	ssize_t	i[2];

	if (!line)
		return (NULL);
	room_init(&room, status);
	tab = ft_strsplit_blanks(line);
	i[0] = -1;
	while (tab[++(i[0])]);
	i[1] = i[0] - 1;
	room.coord[0] = (size_t)ft_atoi(tab[i[1] - 1]);
	room.coord[1] = (size_t)ft_atoi(tab[i[1]]);
	room.key = tab[0];
	i[1]--;
	i[0] = 0;
	while (++(i[0]) < i[1])
		room.key = ft_strjoin_free(room.key, 1, tab[i[0]], 0);
	ret = ft_lstnew((void *)(&room), sizeof(t_room));
	ft_stabdel(&tab);
	return (is_duplicate(ret) ? NULL : ret);
}

_Bool	add_room(t_list **roomlist, char *line, t_flag status)
{
	if (!(roomlist && line && *line))
		return (0);
	if (*roomlist)
		ft_lstadd(roomlist, get_room(line, status));
	else
		*roomlist = get_room(line, status);
	return (1);
}
