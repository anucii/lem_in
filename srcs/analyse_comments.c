/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse_comments.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 17:17:42 by jdaufin           #+#    #+#             */
/*   Updated: 2017/10/11 17:21:38 by jdaufin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

_Bool	is_start(void *content)
{
	char	*line;

	if (!content)
		return (0);
	line = (char *)content;
	return (is_comment(line) ? ft_strequ(line, "##start") : 0);
}

_Bool	is_end(void *content)
{
	char	*line;

	if (!content)
		return (0);
	line = (char *)content;
	return (is_comment(line) ? ft_strequ(line, "##end") : 0);
}
