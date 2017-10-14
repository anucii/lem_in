/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pathlist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/13 19:31:13 by jdaufin           #+#    #+#             */
/*   Updated: 2017/10/13 19:43:48 by jdaufin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_list	*init_pathes(t_list **pathes, ssize_t i)
{
	if (!pathes)
		return (NULL);
}

static t_list	*read_path(t_list **pathes, ssize_t i)
{
	if (!pathes)
		return (NULL);
}

static t_list	*clear_pathes(t_list **pathes, ssize_t i)
{
	if (!pathes)
		return (NULL);
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
