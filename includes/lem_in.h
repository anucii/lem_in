/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 20:05:42 by jdaufin           #+#    #+#             */
/*   Updated: 2017/10/04 14:38:54 by jdaufin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include "libftprintf.h"
# include <stdio.h>
# include <limits.h>

typedef enum	e_err
{
	NOERR = -1, SYSTEM, PARSING
}				t_err;

typedef struct	s_errctrl
{
	t_err		errtype;
	void		(*func)(char *);
}				t_errctrl;

typedef struct	s_options
{
	_Bool		fail_report;
}				t_options;

typedef	enum	e_flag
{
	NOFLG = -1, START, STD, END
}				t_flag;

typedef enum	e_cmd
{
	NOCMD = -1, INIT, EDIT, READ, CLEAR
}				t_cmd;

typedef struct	s_room
{
	char		*key;
	_Bool		is_free;
	t_flag		status;
	size_t		coord[2];
	t_list		*tubes;
}				t_room;

typedef struct	s_neighbr
{
	t_room		*neighbr;
	ssize_t		cost;
}				t_neighbr;

typedef struct	s_ant
{
	ssize_t		id;
	t_room		*pos;
}				t_ant;

typedef struct	s_statement
{
	char		*pattern;
	void		(*func)(void *);
}				t_statement;

typedef struct	s_strcmd
{
	t_cmd		cmd;
	t_list		*(*func)(t_list **);
}				t_strcmd;

t_options		*ft_options(char *pattern);
void			ft_error(t_err errtype, char *msg, _Bool stop);
void			get_input(void);
t_list			*store_input(t_cmd cmd);
_Bool			ft_parse_input(t_list **alst);
t_list			*ft_antlist(t_cmd cmd, ssize_t i);
t_list			*ft_roomlist(t_cmd cmd, char *key);

#endif
