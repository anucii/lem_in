/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/13 19:53:51 by jdaufin           #+#    #+#             */
/*   Updated: 2017/10/18 19:45:40 by jdaufin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

_Bool	is_parent(char *key, t_list *parents)
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

t_list	*ctrl_list(char *elmt)
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

_Bool	set_weights(void)
{
	t_list	*roomlist;
	t_room	*cur;

	if (!(roomlist = ft_roomlist(READ, NULL)))
		return (0);
	while (roomlist && ((cur = (t_room *)roomlist->content)->status != END))
		roomlist = roomlist->next;
	return (get_weight(&cur));
}
