/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_room.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 16:43:25 by jdaufin           #+#    #+#             */
/*   Updated: 2017/10/04 17:38:51 by jdaufin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static _Bool	check_coord(char *s)
{
	char		**stab;
	intmax_t	val;
	ssize_t		i;
	ssize_t		j;

	if (!(s && is_room(s)))
		return (0);
	i = -1;
	j = 3;
	while (stab[++i]);
	while (--i && --j)
	{
		val = ft_atoimax(stab[i]);
		if ((val < 0) || (val > INT_MAX))
		{
			ft_error(PARSING, "Warning : outbound coordinates", 0);
			return (0);
		}
	}
	ft_stabdel(stab);
	return (1);
}

_Bool	is_room(char *s)
{
	char	**stab;
	ssize_t	i;

	if (!(s && *s))
		return (0);
	i = -1;
	stab = ft_strsplit_blanks(s);
	while (stab[++i]); //nb : i stops on index of null slot
	ft_stabdel(stab);
	if (i < 3)
		ft_error(PARSING, "Warning : room definition misses arguments", 0);
	return (i < 3 ? 0 : 1);
}

_Bool	check_room(char *s)
{
	if (!(s && *s && is_room(s)))
		return (0);
	if ((*s == '#') || (*s == 'L') || (ft_strchr(s, (int)'-')))
	{
		ft_error(PARSING,\
				"Warning : forbidden characters in room definition", 0);
		return (0);
	}
	if (!check_coord(s))
	{
		ft_error(PARSING, "Warning : unvalid coordinates", 0);
		return (0);
	}
	return (1);
}
