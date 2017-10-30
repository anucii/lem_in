/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 21:23:48 by jdaufin           #+#    #+#             */
/*   Updated: 2017/10/31 00:17:05 by jdaufin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_room	*get_nroom(t_matches ctrlr, t_list *pathlist)
{
	ssize_t	i;
	t_list	*buf;
	t_list	*res;

	if (!pathlist || (ctrlr.ant_id == -1))
		return (NULL);
	i = -1;
	buf = pathlist;
	while (buf && (++i < ctrlr.path))
		buf = buf->next;
	if (!buf)
		return (NULL);
	i = -1;
	buf = (t_list *)buf->content;
	while (buf && (++i < ctrlr.step))
		buf = buf->next;
	res = buf && buf->content ? ft_roomlist(READ, (char *)buf->content) : NULL;
	return (res ? (t_room *)(res->content) : NULL);
}
/*
static t_ant	*get_ant(ssize_t id, t_list *antlist)
{
	ssize_t	i;
	t_list	*buf;

	if (!antlist || (id == -1))
		return (NULL);
	i = -1;
	buf = antlist;
	while (buf && (++i < id))
		buf = buf->next;
	return (buf && buf->content ? (t_ant *)buf->content : NULL);
}
*/

void			move_ants(t_matches *path_ctrl, t_list *pathlist)
{
	t_ant	*ant_buf;
	t_room	*next_room;
	t_list	*buf;
	ssize_t	i;

	if (!(path_ctrl && pathlist))
		ft_error(PARSING, "Error : missing data to control movements", 1);
	i = -1;
	while (path_ctrl[++i].ant_id != -1)
	{
		buf = ft_antlist(READ, path_ctrl[i].ant_id);
		ant_buf = buf ? (t_ant *)(buf->content) : NULL;
		next_room = ant_buf ? get_nroom(path_ctrl[i], pathlist) : NULL;
		if (next_room && (next_room->is_free || (next_room->status == START)\
					|| (next_room->status == END)))
		{
			ant_buf->pos = next_room;
			ant_buf->display = 1;
			next_room->is_free = 0;
			path_ctrl[i].step++;
		}
		/*
		else
			break ;
			*/
	}
}
