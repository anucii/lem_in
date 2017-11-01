/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 18:08:55 by jdaufin           #+#    #+#             */
/*   Updated: 2017/11/01 22:30:35 by jdaufin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	init_matches(t_matches *path_ctrl, t_list *antlist,\
		t_list *pathlist)
{
	ssize_t	max[2];
	ssize_t	i[3];
	t_list	*buf;

	if (!(path_ctrl && antlist && pathlist))
		ft_error(PARSING, "Error : pathes/rooms/ants not defined", 1);
	max[0] = ft_lstlen(antlist);
	path_ctrl[max[0]] = (t_matches){-1, -1, -1};
	max[1] = 0;
	i[0] = -1;
	i[1] = 0;
	buf = pathlist;
	while (buf && (max[1] < max[0]))
	{
		max[1] += ft_lstlen((t_list *)buf->content) - 2;
		i[1]++;
		buf = buf->next;
	}
	while (++i[0] < max[0])
		path_ctrl[i[0]] = (t_matches){i[0] + 1, i[0] % i[1], 0};
}

_Bool		solver(void)
{
	t_list		*antlist;
	t_list		*pathlist;
	t_matches	*path_ctrl;
	ssize_t		size;

	antlist = ft_antlist(READ, 1);
	pathlist = ft_pathlist(READ, 0);
	if (!(antlist && pathlist))
		ft_error(PARSING, "Error : pathes/rooms/ants not defined", 1);
	size = 1 + ft_lstlen(antlist);
	if ((path_ctrl = (t_matches *)ft_memalloc(size * sizeof(t_matches))))
		init_matches(path_ctrl, antlist, pathlist);
	else
		ft_error(PARSING, "Error : roadmap control structure alloc failure", 1);
	return (ft_itinerary(&path_ctrl, antlist, pathlist));
}
