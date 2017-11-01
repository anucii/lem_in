/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_lem_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 17:50:58 by jdaufin           #+#    #+#             */
/*   Updated: 2017/11/01 22:14:04 by jdaufin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	ft_display(t_list *lst)
{
	t_list *buf;

	if (!lst)
		return ;
	buf = lst;
	while (buf)
	{
		if (buf->content)
			ft_printf("%s\n", (char *)buf->content);
		buf = buf->next;
	}
}

void		exec_lem_in(void)
{
	t_list	*stored_input;

	get_input();
	if (!(stored_input = store_input(READ)))
		ft_error(PARSING, "Error : no valid input", 1);
	if (!ft_antlist(INIT, -1))
		ft_error(PARSING, "Error : ants list could not be set", 1);
	if (!ft_roomlist(INIT, NULL))
		ft_error(PARSING, "Error : rooms could not be set", 1);
	init_weights();
	set_weights();
	if (!ft_pathlist(INIT, -1))
		ft_error(PARSING, "Error : solutions list could not be set", 1);
	ft_display(stored_input);
	if (!solver())
		ft_error(PARSING, "Error : could not solve the map", 1);
	ft_antlist(CLEAR, -1);
	ft_roomlist(CLEAR, NULL);
	ft_pathlist(CLEAR, -1);
	store_input(CLEAR);
}

int			main(int ac, char *av[])
{
	size_t	i;

	i = 0;
	if (ac > 1)
	{
		while (av[++i])
			if (av[i][0] == '-')
				ft_options(av[i]);
	}
	exec_lem_in();
}
