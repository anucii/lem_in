/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 18:41:33 by jdaufin           #+#    #+#             */
/*   Updated: 2017/10/26 17:43:15 by jdaufin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		rm_first_tube(t_list *startroom)
{
	t_room	*room;
	t_list	*tubes;

	if (!startroom)
		ft_error(PARSING, "Error : first startroom's tube removal failure", 1);
	room = (t_room *)startroom->content;
	tubes = room->tubes;
	room->tubes = room->tubes->next;
	ft_lstdelone(&tubes, &ft_linkdel);
}

static void		wormhole(void)
{
	t_list			*buf[2];
	t_list			*tubes[2];
	char			*keys[2];

	if (!(buf[0] = get_start()))
		ft_error(PARSING, "Error : starting room cannot be retrieved", 1);
	buf[1] = ((t_room *)buf[0]->content)->tubes;
	keys[0] = ((t_room *)(get_end()->content))->key;
	if (buf[1] && ft_strequ(keys[0], (char *)buf[1]->content))
		rm_first_tube(buf[0]);
	else
		while (buf[1])
		{
			tubes[0] = buf[1];
			tubes[1] = buf[1]->next;
			keys[1] = tubes[1] ? (char *)tubes[1]->content : NULL;
			if (keys[1] && ft_strequ(keys[0], keys[1]) && tubes[1])
			{
				tubes[0]->next = tubes[1]->next;
				ft_lstdelone(&tubes[1], &ft_linkdel);
			}
			buf[1] = buf[1]->next;
		}
}

static char		*extract_lightest_tube(t_list *tubes)
{
	t_list			*buf[3];
	char			*keys[2];
	int				weight[2];

	if (!tubes)
		return (NULL);
	buf[2] = tubes;
	weight[1] = INT_MAX / 2;
	keys[1] = NULL;
	while (buf[2])
	{
		if ((keys[0] = (char *)buf[2]->content))
			if ((buf[0] = ft_roomlist(READ, keys[0])) && (((t_room *)\
							buf[0]->content)->status != START))
			{
				weight[0] = ((t_room *)buf[0]->content)->weight;
				keys[1] = weight[0] < weight[1] ? keys[0] : keys[1];
				weight[1] = weight[0] < weight[1] ? weight[0] : weight[1];
			}
		buf[2] = buf[2]->next;
	}
	if (weight[1] < (INT_MAX / 2) && (buf[1] = ft_roomlist(READ, keys[1])))
		((t_room *)buf[1]->content)->weight =\
			((t_room *)buf[1]->content)->status == END ? 0 : INT_MAX / 2;
	return (weight[1] < (INT_MAX / 2) ? keys[1] : NULL);
}

t_list			*get_path(void)
{
	t_list	*buf[2];
	t_list	*ret;
	char	*key;

	if (!(buf[0] = get_start()))
		return (NULL);
	if (!(key = ((t_room *)buf[0]->content)->key))
		return (NULL);
	if (!(ret = ft_lstnew((void *)key, 1 + ft_strlen(key))))
		return (NULL);
	if (!(buf[1] = ((t_room *)buf[0]->content)->tubes))
		return (NULL);
	while (buf[0] && (((t_room *)buf[0]->content)->status != END) && buf[1]\
			&& (key = extract_lightest_tube(buf[1])))
	{
		ft_lstappend(&ret, ft_lstnew((void *)key, 1 + ft_strlen(key)));
		buf[0] = ft_roomlist(READ, key);
		buf[1] = ((t_room *)buf[0]->content)->tubes;
	}
	if (ret && (ft_lstlen(ret) == 2))
		wormhole();
	return (key ? ret : NULL);
}
