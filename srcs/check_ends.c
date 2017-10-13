/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ends.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/13 18:48:52 by jdaufin           #+#    #+#             */
/*   Updated: 2017/10/13 18:57:16 by jdaufin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

_Bool	check_ends(void)
{
	t_list	*roomlist;
	t_room	*room;
	ssize_t	counts[2];

	if (!(roomlist = ft_roomlist(READ, NULL)))
		return (0);
	counts[0] = 0;
	counts[1] = 0;
	while (roomlist)
	{
		room = (t_room *)(roomlist->content);
		counts[0] += room->status == START ? 1 : 0;
		counts[1] += room->status == END ? 1 : 0;
		if ((counts[0] > 1) || (counts[1] > 1))
			return (0);
		roomlist = roomlist->next;
	}
	return ((counts[0] == 1) && (counts[1] == 1) ? 1 : 0);
}
