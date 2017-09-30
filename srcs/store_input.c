/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 19:04:47 by jdaufin           #+#    #+#             */
/*   Updated: 2017/09/30 21:25:01 by jdaufin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_list	*init_input(t_list *ptr)
{
	int		gnl;
	char	*line;
	t_list	*buf;

	if (!ptr)
		ft_error(SYSTEM, "Input acquisition failure due to malloc error", 1);
	buf = ptr;
	while ((gnl = get_next_line(0, &line)) > 0)
	{
		ft_lstinsert(&buf, ft_lstnew((void *)line, ft_strlen(line) + 1));
		buf = buf->next;
	}
	if (gnl == -1)
		ft_error(SYSTEM, "STDIN acquisition error", 0);
	return (ptr); 
	/* Shouldn't the returning of ptr be reserved to read_input ?
	 */
}

static t_list	*read_input(t_list *ptr)
{
	if (ptr && ptr->content)
		return (ptr);
	return (NULL);
}

static t_list	*clear_input(t_list *ptr)
{
	if (!ptr)
		ft_error(PARSING, "Invalid clearing request of void input", 1);
	ft_lstdel(&ptr, &ft_linkdel);
	return (ptr ? ptr : NULL);
}

t_list			*store_input(t_cmd cmd)
{
	static t_list	*input = ft_memalloc(sizeof(t_list));
	static t_strcmd	*actions = {{INIT, &init_input}, {READ, &read_input},\
		{CLEAR, &clear_input}, {NONE, NULL}};
	ssize_t			i;

	i = -1;
	while (actions[++i]->cmd != NONE)
	{
		if (actions[i]->cmd == cmd)
			return ((actions[i]->func)(input));
	}
	return (NULL);
}
