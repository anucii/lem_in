/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pathlist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/13 19:31:13 by jdaufin           #+#    #+#             */
/*   Updated: 2017/11/01 22:09:06 by jdaufin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_list	*init_pathes(t_list **pathes, ssize_t i)
{
	t_list	*buf[2];
	t_list	*tmp;

	if (!pathes)
		return (NULL);
	i = 0;
	buf[0] = NULL;
	if (!(check_ends() && (buf[0] = get_path())))
		ft_error(PARSING, "Error : no valid solution to the given map", 1);
	if (!(*pathes = ft_lstnew((void *)buf[0], sizeof(t_list))))
		ft_error(SYSTEM, "Error : could not init solutions list", 1);
	while ((buf[1] = get_path()))
		ft_lstappend(pathes, tmp = ft_lstnew((void *)buf[1], sizeof(t_list)));
	if (!(*pathes))
		ft_error(PARSING, "Error : no valid solution", 1);
	return (*pathes);
}

static t_list	*read_path(t_list **pathes, ssize_t i)
{
	t_list	*buf;
	ssize_t	j;

	if (!(pathes && (buf = *pathes)))
		return (NULL);
	j = -1;
	while (buf && (++j < i))
		buf = buf->next;
	return (buf);
}

static t_list	*clear_pathes(t_list **pathes, ssize_t i)
{
	t_list	*buf[1];

	if (!pathes)
		ft_error(PARSING, "Error : cleansing called on void pathlist", 1);
	i = 0;
	buf[0] = *pathes;
	while (buf[0])
	{
		if (buf[0]->content)
			ft_lstdel((t_list **)&(buf[0]->content), &ft_linkdel);
		buf[0] = buf[0]->next;
	}
	ft_lstdel(pathes, &ft_linkdel);
	ft_memdel((void **)pathes);
	return (pathes && *pathes ? *pathes : NULL);
}

t_list			*ft_pathlist(t_cmd cmd, ssize_t i)
{
	ssize_t					j;
	static t_list			*lst = NULL;
	static const t_strcmd	actions[4] = (const t_strcmd[]){{INIT,\
		{NULL, &init_pathes, NULL}}, {READ, {NULL, &read_path, NULL}},\
	{CLEAR, {NULL, &clear_pathes, NULL}}, {NOCMD, {NULL, NULL, NULL}}};

	j = -1;
	while (actions[++j].cmd != NOCMD)
	{
		if (actions[j].cmd == cmd)
			return (actions[j].func.dualf(&lst, i));
	}
	return (NULL);
}
