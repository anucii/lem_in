/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 13:07:42 by jdaufin           #+#    #+#             */
/*   Updated: 2017/10/04 14:34:10 by jdaufin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static _Bool	parse_antline(char *s)
{
	int		val;
	ssize_t	i;
	if (!(s && *s))
		return (0);
	i = *s == '+' ? 0 : -1;
	while (ft_isdigit(s[++i]));
	if ((size_t)i < ft_strlen(s))
	{
		ft_error(PARSING, "File error : forbidden characters in first line",\
				1);
		return (0);
	}
	val = ft_atoimax(s);
	if (val == 0)
	{
		ft_error(PARSING, "Error : null ant value", 1);
		return (0);
	}
	return ((val < INT_MAX) && (val > 0) ? 1 : 0);
}

static _Bool	parse_map(char *s)
{
	if (!(s && *s))
		return (0);
	return (1);
}

_Bool	ft_parse_input(t_list **alst)
{
	static t_list	*buf;

	if (alst)
	{
		buf = *alst;
		return (buf ? parse_antline((char *)buf->content) : 0);
	}
	else if (buf)
	{
		buf = buf->next;
		return (buf ? parse_map((char *)buf->content) : 1);
	}
	else
	{
		ft_error(PARSING, "Warning : could not parse due to void input", 0);
		return (0);
	}
}
