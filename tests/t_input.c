#include "lem_in.h"
#include <sys/wait.h>

void	t_display(t_list *lst)
{
	t_list	*buf;

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

void	t_showants(void)
{
	t_list	*anthill;
	t_list	*buf;
	ssize_t i[2];

	if (!(anthill = ft_antlist(INIT, -1)))
		return ;
	i[0] = 0;
	i[1] = ft_lstlen(anthill);
	while (++(i[0]) <= i[1])
	{
		if ((buf = ft_antlist(READ, i[0])))
			ft_printf("Ant ID : %zu\nAnt pos: %p\nDisplay state :%s\n\n",\
					((t_ant *)(buf->content))->id, ((t_ant *)(buf->content))->pos,\
					((t_ant *)(buf->content))->display ? "True" : "False");
	}
}

void	print_room(t_list *ptr)
{
	t_room	*room;

	if (!ptr)
		return ;
	room = (t_room*)ptr->content;
	ft_printf("%s (status : %u) @ [%zu, %zu]\n", room->key, room->status,\
			room->coord[0], room->coord[1]);
}

void	print_roomlist(t_list *ptr)
{
	if (!ptr)
		return ;
	while (ptr)
	{
		print_room(ptr);
		ptr = ptr->next;
	}
}

void	t_rooms(void)
{
	t_list	*roomlist;
	ssize_t	i = -1;
	char 	*user[6] = (char *[]){"home", "rudys", "luans", "elsewhere",\
		"all" , NULL};

	ft_roomlist(INIT, NULL);
/*
	ft_putendl("Type \"all\" to show all rooms, or a specific name to show one");
	ft_putendl("Type \"STOP\" to stop the process");
	ft_printf("TEST : %s\n", user);
	ft_printf("isatty(0) return = %d\n", isatty(0));
	while (get_next_line(0, (void *)user) == 1)
	{
		ft_printf("user input %s\n", user);
		roomlist = ft_roomlist(READ, user);
		if (ft_strequ(user, "all"))
			print_roomlist(roomlist);
		else
			print_room(roomlist);
		//ft_putendl("");
	}	
	*/
	while (user[++i])
	{
		roomlist = ft_roomlist(READ, user[i]);
		print_room(roomlist);
	}
	ft_printf("\nRooms list recap:\n");
	roomlist = ft_roomlist(READ, NULL);
	print_roomlist(roomlist);
}

int		main(int ac, char **av)
{
	t_list	*stored_input = NULL;
	size_t	i = 0;
//	int		waiter = 0;

	if (ac > 1)
	{
		while (av[++i])
			if (av[i][0] == '-')
				ft_options(av[i]);
	}
	get_input();
	stored_input = store_input(READ);
	ft_printf("Input stored at %p\n", stored_input);
	t_display(stored_input);
	t_showants();
	t_rooms();
	if (!(ft_antlist(CLEAR, -1)))
		ft_putendl("Anthill now void");
	if (!(ft_roomlist(CLEAR, NULL)))
		ft_putendl("Roomlist cleared");
	store_input(CLEAR);
/*	while (1)
	  wait(&waiter);
*/	
	return (0);
}
