/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_flag.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 17:06:03 by jdaufin           #+#    #+#             */
/*   Updated: 2017/10/11 17:10:34 by jdaufin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_flag	status_flag(t_flag input)
{
	static t_flag	ret = STD;

	if (input != NOFLG)
		ret = input;
	return (ret);
}
