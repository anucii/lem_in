/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 17:53:12 by jdaufin           #+#    #+#             */
/*   Updated: 2017/11/01 22:29:36 by jdaufin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	get_input(void)
{
	t_list	*input;

	if (!(input = store_input(INIT)))
		ft_error(PARSING, "Unvalid input storage request", 1);
}
