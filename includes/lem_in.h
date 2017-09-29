/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 20:05:42 by jdaufin           #+#    #+#             */
/*   Updated: 2017/09/29 21:14:36 by jdaufin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include "libftprintf.h"

typedef	enum	e_flag
{
	START, STD, END
}				t_flag;

typedef struct	s_room
{
				char	*key;
				_Bool	is_free;
				t_flag	status;
				size_t	coord[2];
				t_list	*tubes;
}				t_room;

typedef struct	s_neighbr
{
				t_room	*neighbr;
				ssize_t	cost;
}				t_neighbr;

typedef struct	s_ant
{
				ssize_t	id;
				t_room	*pos;
}				t_ant;

#endif
