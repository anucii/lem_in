/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_antlist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 18:12:40 by jdaufin           #+#    #+#             */
/*   Updated: 2017/10/10 13:43:29 by jdaufin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_list	*ft_antinit(t_list **anthill, ssize_t i)
{
	ssize_t	j;
	t_ant	ant;

	if (!anthill || i < 1)
		return (NULL);
	j = 0;
	*anthill = NULL;
	while (++j <= i)
	{
		ant = (t_ant){j, NULL, 0};
		if (!(*anthill))
			 *anthill = ft_lstnew((void *)&ant, sizeof(t_ant));
		else
			ft_lstappend(anthill, ft_lstnew((void *)&ant, sizeof(t_ant)));
	}
	return (*anthill);
}

static t_list	*ft_antread(t_list **anthill, ssize_t i)
{
	ssize_t	j;
	t_list	*buf;

	if (!(anthill && *anthill))
		return (NULL);
	if (i > (ssize_t)ft_lstlen(*anthill))
		ft_error(PARSING, "Warning: attempt to read an unexistant ant", 0);
	j = 0;
	buf = *anthill;
	while (buf && (++j < i))
		buf = buf->next;
	if ((j == i) && buf && (((t_ant *)(buf->content))->id == i))
		return (buf);
	ft_error(PARSING, "Warning : invalid ant reading request", 0);
	return (NULL);
}

static t_list	*ft_antclear(t_list **anthill, ssize_t i)
{
	(void)i;
	if (!(anthill && *anthill))
	{
		ft_error(PARSING, "Warning : unvalid attempt to clear a void anthill",\
				0);
		return (NULL);
	}
	ft_lstdel(anthill, &ft_linkdel);
	ft_memdel((void **)anthill);
	return (anthill && *anthill ? *anthill : NULL);
}

t_list			*ft_antlist(t_cmd cmd, ssize_t i)
{
	static t_list			*lst = NULL;
	static const t_strcmd	commands[4] = (const t_strcmd[]){{INIT,\
		{&ft_antinit}}, {READ, {&ft_antread}}, {CLEAR, {&ft_antclear}},\
	{NOCMD, {NULL}}};
	t_list					*input;
	ssize_t					j;

	if (!(input = store_input(READ)))
		return (NULL);
	j = -1;
	if (i == -1)
		i = (ssize_t)ft_atoi((char *)input->content);
	while (commands[++j].cmd != NOCMD)
		if (commands[j].cmd == cmd)
			return (commands[j].u_func.dualf(&lst, i));
	return (NULL);
}
