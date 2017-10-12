/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_roomlist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 13:53:26 by jdaufin           #+#    #+#             */
/*   Updated: 2017/10/12 18:28:34 by jdaufin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		ft_init(char **astr, t_list **input)
{
	if (!(astr && input))
		return ;
	*astr = NULL;
	*input = (*input)->next;
	status_flag(STD);
}

static t_list	*ft_readlist(t_list **roomlist, char *key)
{
	t_list	*buf;

	if (!roomlist)
		return (NULL);
	if (!key || ft_strequ(key, "all"))
		return (*roomlist);
	else
	{
		buf = *roomlist;
		while (buf && ft_strcmp(((t_room *)(buf->content))->key, key))
			buf = buf->next;
		return (buf);
	}
}

static t_list	*ft_roominit(t_list **rms, char *key)
{
	t_list	*input;

	if (!(rms && (input = store_input(READ))))
		return (NULL);
	ft_init(&key, &input);
	while (input && !is_tube((char *)(input->content)))
	{
		if (is_start(input->content) || is_end(input->content))
			is_end(input->content) ? status_flag(END) : status_flag(START);
		else if ((!is_comment((char *)(input->content))))
		{
				if (!(is_room((char *)(input->content)) && add_room(rms,\
								(char *)(input->content), status_flag(NOFLG))))
					ft_error(PARSING, "Warning : room could not be set", 0);
				status_flag(STD);
		}
		input = input->next;
	}
/*	while (input && is_tube((char *)(input->content)))
	{
		if (!add_tube(rms, (char *)(input->content)))
			ft_error(PARSING,"Warning : edges setting interrupted" , 0);
		input = input->next;
	}
	*/
	return (*rms);
}

static t_list	*clear_rooms(t_list **roomlist, char *key)
{
	t_list	*buf;

	if (!roomlist)
		return (NULL);
	key = NULL;
	buf = *roomlist;
	while (buf)
	{
		if (((t_room *)(buf->content))->key)
			ft_strdel(&(((t_room *)(buf->content))->key));
		if (((t_room *)(buf->content))->tubes)
			ft_lstdel(&(((t_room *)(buf->content))->tubes), &ft_linkdel);
		buf = buf->next;
	}
	ft_lstdel(roomlist, &ft_linkdel);
	ft_memdel((void **)(roomlist));
	return (roomlist && *roomlist ? *roomlist : NULL);
}

t_list	*ft_roomlist(t_cmd cmd, char *key)
{
	ssize_t						i;
	static t_list				*roomlist = NULL;
	static const t_strcmd		actions[4]= (const t_strcmd[]){{INIT,\
		{NULL, NULL, &ft_roominit}}, {READ, {NULL, NULL, &ft_readlist}},\
	{CLEAR, {NULL, NULL, &clear_rooms}}, {NOCMD, {NULL, NULL, NULL}}};

	i = -1;
	while (actions[++i].cmd != NOCMD)
	{
		if (actions[i].cmd == cmd)
			return (actions[i].func.keyf(&roomlist, key));
	}
	return (NULL);
}
