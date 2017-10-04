/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 19:04:47 by jdaufin           #+#    #+#             */
/*   Updated: 2017/10/04 14:28:06 by jdaufin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_list	*init_input(t_list **ptr)
{
	int		gnl;
	char	*line;
	_Bool	check;

	if (!(ptr))
		ft_error(SYSTEM, "Input acquisition failure due to malloc error", 1);
	*ptr = NULL;
	check = 1;
	while (check && ((gnl = get_next_line(0, &line)) > 0))
	{
		if (*ptr)
			ft_lstappend(ptr, ft_lstnew((void *)line, ft_strlen(line) + 1));
		else
			*ptr = ft_lstnew((void *)line, ft_strlen(line) + 1);
		ft_memdel((void **)&line);
		check = ft_parse_input(ptr);
	}
	if (!check)
		ft_error(PARSING, "Warning : file syntax error", 0);
	if (gnl == -1)
		ft_error(SYSTEM, "STDIN acquisition error", 0);
	return (*ptr);
	/* Shouldn't the returning of ptr be reserved to read_input ?
	 */
}

static t_list	*read_input(t_list **ptr)
{
	if (ptr && *ptr && (*ptr)->content)
		return (*ptr);
	return (NULL);
}

static t_list	*clear_input(t_list **ptr)
{
	if (!(ptr && *ptr))
		ft_error(PARSING, "Invalid clearing request of void input", 1);
	ft_lstdel(ptr, &ft_linkdel);
	ft_memdel((void **)ptr);
	return (ptr && *ptr ? *ptr : NULL);
}

t_list			*store_input(t_cmd cmd)
{
	static t_list			*input;
	static const t_strcmd	actions[4] = (const t_strcmd[]){{INIT,\
		&init_input},{READ, &read_input}, {CLEAR, &clear_input},\
		{NOCMD, NULL}};
	ssize_t					i;

	i = -1;
	while (actions[++i].cmd != NOCMD)
	{
		if (actions[i].cmd == cmd)
			return ((actions[i].func)(&input));
	}
	return (NULL);
}
