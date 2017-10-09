/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_tube.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 16:43:46 by jdaufin           #+#    #+#             */
/*   Updated: 2017/10/09 15:58:27 by jdaufin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

_Bool	is_tube(char *s)
{
	if (!(s && *s && ft_strchr(s, '-')))
		return (0);
	return (1);
}

_Bool	check_tube(char *s)
{
//	char	*trim;

	if (!(s && is_tube(s)))
		return (0);
//	trim = ft_strtrim(s);
	if ((ft_wordcount(s, '-') != 2))
	{
//		ft_strdel(&trim);
		return (0);
	}
//	else
//		ft_strdel(&trim);
	return (1);
}
