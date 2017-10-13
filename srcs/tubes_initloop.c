/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tubes_initloop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/13 16:04:17 by jdaufin           #+#    #+#             */
/*   Updated: 2017/10/13 16:11:11 by jdaufin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	tubes_initloop(t_list **roomlist, t_list *input)
{
	if (!(roomlist && input))
		return ;
	while (input && is_tube((char *)(input->content)))
	{
		if (!add_tube(roomlist, (char *)(input->content)))
			ft_error(PARSING,"Warning : edges setting interrupted" , 0);
		input = input->next;
	}
}
