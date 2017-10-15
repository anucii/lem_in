/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_weight.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/15 15:27:06 by jdaufin           #+#    #+#             */
/*   Updated: 2017/10/15 15:59:07 by jdaufin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static short		last_room(t_room **room)
{
	if (!(room && *room && ((*room)->status == END)))
		return (SHRT_MIN);
	(*room)->weight = 0;
	return (0);
}

static t_list		*reset_parent(t_list **backup)
{
	t_list	*ret;
	t_list	*start;

	ctrl_list("htkc-2#0");
	if (!(backup && *backup))
		return (NULL);
	start = *backup;
	while (*backup)
	{
		ret = ctrl_list((char *)(*backup)->content);
		*backup = (*backup)->next;
	}
	if (start)
		ft_lstdel(&start, &ft_linkdel);
	return (ret);
}

short				get_weight(t_room **room, t_list *parents)
{
	t_list	*mates;
	t_list	*buf[2];
	short	cand;

	if (!(room && *room && (mates = (*room)->tubes)))
		return (SHRT_MIN);
	if ((*room)->status == END)
		return (last_room(room));
	while (mates)
	{
		if ((*room)->status == START)
			ctrl_list((*room)->key);
		buf[0] = parents ? ft_lstdup(parents) : NULL;
		if ((buf[1] = ft_roomlist(READ, (char *)(mates->content))) && \
				(!is_parent(((t_room *)(buf[1]->content))->key, parents)))
		{
			cand = 1 + get_weight((t_room **)&(buf[1]->content),\
					ctrl_list((char *)mates->content));
			(*room)->weight = cand < (*room)->weight ? cand : (*room)->weight;
		}
		parents = reset_parent(&buf[0]);
		mates = mates->next;
	}
	return ((*room)->weight);
}
