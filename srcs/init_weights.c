/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_weights.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/13 19:03:30 by jdaufin           #+#    #+#             */
/*   Updated: 2017/11/01 22:30:02 by jdaufin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

_Bool	init_weights(void)
{
	t_list	*roomlist;
	t_room	*room;

	if (!(roomlist = ft_roomlist(READ, NULL)))
	{
		ft_error(PARSING, "Error : roomlist could not be read.", 1);
		return (0);
	}
	while (roomlist)
	{
		room = (t_room *)(roomlist->content);
		room->weight = room->status == START ? 0 : (INT_MAX / 2);
		roomlist = roomlist->next;
	}
	return (1);
}
