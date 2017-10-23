/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 18:41:33 by jdaufin           #+#    #+#             */
/*   Updated: 2017/10/23 19:40:59 by jdaufin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static _Bool	wormhole(_Bool set)
{
	static _Bool	ret = 0;

	if (set)
		ret = 1;
	return (ret);
}

static char		*extract_lightest_tube(t_list *tubes, ssize_t i)
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
		if ((keys[0] = (char *)buf[2]->content) && (buf[0] =\
					ft_roomlist(READ, keys[0])) && (((t_room *)buf[0]->content)\
					->status != START) && !(wormhole(0) && (i > 0)\
						&& ((t_room *)buf[0]->content)->status == END))
		{
			weight[0] = ((t_room *)buf[0]->content)->weight;
			keys[1] = weight[0] < weight[1] ? keys[0] : keys[1];
			weight[1] = weight[0] < weight[1] ? weight[0] : weight[1];
		}
		buf[2] = buf[2]->next;
	}
	if (weight[1] < (INT_MAX / 2) && (buf[1] = ft_roomlist(READ, keys[1])))
	{
		((t_room *)buf[1]->content)->weight = ((t_room *)buf[1]->content)\
											  ->status == END ? 0 : INT_MAX / 2;
		ft_printf("Recorded step : %s (weight : %d)\n", keys[1], weight[1]);//dbg
		ft_error(PARSING, "DBG : selected room closed", 0);//suppress!!
	}
	return (weight[1] < (INT_MAX / 2) ? keys[1] : NULL);
}

t_list			*get_path(t_list *rooms)
{
	t_list	*buf[2];
	t_list	*ret;
	char	*key;
	ssize_t	i;

	i = -1;
	if (!((rooms && (buf[0] = get_start(rooms))) && (key = \
				((t_room *)buf[0]->content)->key)))
		return (NULL);
	if (!(ret = ft_lstnew((void *)key, 1 + ft_strlen(key))))
		return (NULL);
	if (!(buf[1] = ((t_room *)buf[0]->content)->tubes))
		return (NULL);
	while (buf[0] && (((t_room *)buf[0]->content)->status != END) && buf[1]\
			&& (key = extract_lightest_tube(buf[1], ++i)))
	{
		ft_lstappend(&ret, ft_lstnew((void *)key, 1 + ft_strlen(key)));
		buf[0] = ft_roomlist(READ, key);
		buf[1] = ((t_room *)buf[0]->content)->tubes;
	}
	if (ret && (ft_lstlen(ret) == 1))
		wormhole(1);
	ft_putendl_fd(key ? "Path generated" : "No path returned", 2);//dbg
	return (key ? ret : NULL);
}
