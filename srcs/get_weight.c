/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_weight.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/15 15:27:06 by jdaufin           #+#    #+#             */
/*   Updated: 2017/10/19 15:14:58 by jdaufin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void			add_elems(char *parent, t_list *tubes, t_list **to_map)
{
	t_list	*buf;
	t_list	*ctrl;
	t_calls	calls;

	if (!(tubes && to_map && *to_map))
		return ;
	buf = tubes;
	ctrl = ctrl_list(parent);
	while (buf)
	{
		if (!is_parent((char *)buf->content, ctrl))
		{
			calls.caller = parent && *parent ? ft_strdup(parent) : NULL;
			calls.callee = buf->content ? ft_strdup((char *)buf->content)\
						   : NULL;
			ft_lstappend(to_map, ft_lstnew((void *)&calls, sizeof(t_calls)));
		}
		buf = buf->next;
	}
}

static void			init_loop(t_list **to_map, t_room **room)
{
	t_calls	*root;

	if (!(to_map && room && *room))
		return ;
	root = (t_calls[1]){{NULL, (*room)->key}};
	if ((*room)->status != END)
		return ;
	(*room)->weight = 0;
	*to_map = ft_lstnew((void *)root, sizeof(t_calls));
	add_elems((*room)->key, (*room)->tubes, to_map);
}

static void			clean_calls(t_list **map_elem)
{
	t_calls	*calls;

	if (!(map_elem && *map_elem))
		return ;
	calls = (t_calls *)(*map_elem)->content;
	ft_strdel(&(calls->caller));
	ft_strdel(&(calls->callee));
}

_Bool				get_weight(t_room **room)
{
	t_list	*to_map[5];
	t_calls	*buf;
	t_room	*curs[2];

	if (!(room && *room))
		return (0);
	init_loop(&to_map[0], room);
	to_map[2] = to_map[0];
	to_map[0] = to_map[0]->next;
	while (to_map[0])
	{
		buf = (t_calls *)(to_map[0]->content);
		if ((to_map[3] = ft_roomlist(READ, buf->caller)) && (to_map[4] = \
					ft_roomlist(READ, buf->callee)))
		{
			curs[0] = buf->caller ? (t_room *)to_map[3]->content : NULL;
			curs[1] = buf->callee ? (t_room *)to_map[4]->content : NULL;
			add_elems(buf->callee, curs[1]->tubes, (t_list **)&to_map[0]);
			if (curs[0])
				curs[1]->weight = curs[1]->weight < (1 + curs[0]->weight) ?\
								  curs[1]->weight : 1 + curs[0]->weight; 
		}
		to_map[1] = to_map[0]->next;
		clean_calls((t_list **)&to_map[0]);
		to_map[0] = to_map[1];
	}
	ft_lstdel(&to_map[2], &ft_linkdel);
	return (1);
}
