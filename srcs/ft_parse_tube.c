/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_tube.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 16:43:46 by jdaufin           #+#    #+#             */
/*   Updated: 2017/10/12 18:36:36 by jdaufin          ###   ########.fr       */
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
	if (!(s && is_tube(s)))
		return (0);
	if ((ft_wordcount(s, '-') != 2))
		return (0);
	return (1);
}
