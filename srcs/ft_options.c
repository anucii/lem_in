/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_options.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 20:38:41 by jdaufin           #+#    #+#             */
/*   Updated: 2017/10/03 20:54:18 by jdaufin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_options	*ft_options(char *pattern)
{
	static t_options	options = (t_options){0};

	if (!pattern)
		return (&options);
	else if (ft_strequ(pattern, "-e") || ft_strequ(pattern, "--fail-report"))
		options.fail_report = 1;
	else
	{
		ft_error(PARSING, "Argument error : unvalid option", 0);
		return (NULL);
	}
	return (&options);
}
