/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 17:53:12 by jdaufin           #+#    #+#             */
/*   Updated: 2017/10/03 19:52:03 by jdaufin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	get_input(void)
{
//	t_list	*antlist;
	t_list	*input;

	if (!(input = store_input(INIT)))
		ft_error(PARSING, "Unvalid input storage request", 1);
	/*
		if (!(antlist = ft_antlist(INIT, -1)))
		ft_error();
		*/
	// Here : test wether a solution could be found given the stored input.
}
