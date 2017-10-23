/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 18:59:52 by jdaufin           #+#    #+#             */
/*   Updated: 2017/10/23 17:37:48 by jdaufin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_list	*get_start(t_list *rooms)
{
	t_list	*buf;
	if (!rooms)
		return (NULL);
	buf = rooms;
	while (buf && (((t_room *)buf->content)->status != START))
		buf = buf->next;
	return (buf);
}
