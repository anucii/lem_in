/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 13:07:42 by jdaufin           #+#    #+#             */
/*   Updated: 2017/10/05 14:02:20 by jdaufin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static _Bool	parse_antline(char *s)
{
	intmax_t	val;
	ssize_t		i;

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
	if ((val <= 0) || val > (INT_MAX))
	{
		ft_error(PARSING, val ? "Error : ant value out of bounds"\
				: "Error : null or invalid ant value", 1);
		return (0);
	}
	return (1);
}

static _Bool	parse_map(char *s)
{
	static _Bool	switcher[2] = (_Bool [2]){0,0};
	_Bool			check;

	if (!(s && *s))
		return (0);
	check = 0;
	if (is_comment(s))
		return (1);
	else if (!switcher[1] && is_room(s))
	{
		switcher[0] = 1;
		if (!(check = check_room(s)))
			ft_error(PARSING, "Error : unvalid room definition", 1);
		return (check);
	}
	else if (switcher[0] && is_tube(s))
	{
		switcher[1] = 1;
		if (!(check = check_tube(s)))
			ft_error(PARSING, "Warning : unvalid tube definition", 0);
		return (check);
	}
	return (0);
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
