/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/15 13:22:12 by jdaufin           #+#    #+#             */
/*   Updated: 2017/10/15 13:33:37 by jdaufin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_list	*ft_lstdup(t_list *src)
{
	t_list	*buf[3];

	if (!src)
		return (NULL);
	buf[0] = src;
	buf[1] = NULL;
	buf[2] = NULL;
	while (buf[0])
	{
		if (!buf[1])
		{
			if (!(buf[1] = ft_lstnew(buf[0]->content, buf[0]->content_size)))
				return (NULL);
		}
		else
		{
			if (!(buf[2] = ft_lstnew(buf[0]->content, buf[0]->content_size)))
				return (NULL);
			ft_lstadd(&buf[1], buf[2]);
		}
		buf[0] = buf[0]->next;
	}
	return (buf[1]);
}
