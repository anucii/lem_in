/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_weights.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/13 19:03:30 by jdaufin           #+#    #+#             */
/*   Updated: 2017/10/13 19:12:37 by jdaufin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

_Bool	init_weights(void)
{
	t_list	*roomlist;
	t_room	*room;

	if (!(roomlist = ft_roomlist(READ, NULL)))
		return (0);
	while (roomlist)
	{
		room = (t_room *)(roomlist->content);
		room->weight = room->status == START ? 0 : SHRT_MAX;
		roomlist = roomlist->next;
	}
	return (1);
}
