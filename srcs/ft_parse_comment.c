/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_comment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 16:49:41 by jdaufin           #+#    #+#             */
/*   Updated: 2017/10/05 14:01:25 by jdaufin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

_Bool	is_comment(char *s)
{
	return (s && *s && (*s == '#') ? 1 : 0);
}
/*
_Bool	check_comment(char *s)
{
	if (!(s && is_comment(s)))
		return (0);
	if (s[1] == '#')
	{
		if (ft_strcmp(s, "##start") || ft_strcmp(s, "##end"))
			return ()
	}
	return (1);
}
*/
