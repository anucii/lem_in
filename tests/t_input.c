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
	t_list	*tubes;

	if (!ptr)
		return ;
	room = (t_room*)ptr->content;
	ft_printf("%s (status : %u, weight : %d) @ [%zu, %zu]\n", room->key,\
			room->status, room->weight,\
			room->coord[0], room->coord[1]);
	if ((tubes = room->tubes))
	{
		ft_printf("Tubes:");
		while (tubes)
		{
			ft_printf(" %s ", (char *)(tubes->content));
			tubes = tubes->next;
		}
		ft_putendl("");
	}
	else
		ft_printf("No tube at %p\n", &(room->tubes));
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
	char 	*user[6] = (char *[]){"home", "friend", "luans", "elsewhere",\
		"all" , NULL};

	ft_roomlist(INIT, NULL);
	init_weights();
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
		ft_strequ(user[i], "all") ? print_roomlist(roomlist)\
			: print_room(roomlist);
	}
	ft_printf("Weights successfully set ?\n%s\n", set_weights() ? "Yes" : "No");
	ft_printf("\nRooms list recap:\n");
	roomlist = ft_roomlist(READ, "all");
	print_roomlist(roomlist);
}

void	t_pathes(void)
{
	t_list	*buf[2];
	ssize_t	i = -1;

	buf[0] = ft_pathlist(INIT, -1);
	ft_putendl_fd("Pathlist initialized", 2);
	while (buf[0])
	{
		if ((buf[0] = ft_pathlist(READ, ++i))\
					&& (buf[1] = (t_list *)buf[0]->content))
		{
			ft_printf("Path no %zu : ", i);
			while (buf[1] && buf[1]->content)
			{
				ft_printf("%s ", (char *)buf[1]->content);
				buf[1] = buf[1]->next;
			}
			ft_putendl("");
		}
	}
}

int		main(int ac, char **av)
{
	t_list	*stored_input = NULL;
	size_t	i = 0;
	//int		waiter = 0;

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
	ft_printf("Has roomlist exactly one start and end ?\n%s\n",\
			check_ends() ? "Yes": "No");
	t_pathes();
	solver();
	//solver(ft_antlist(READ, 1), ft_pathlist(READ, 0));
	
	if (!(ft_antlist(CLEAR, -1)))
		ft_putendl("Anthill cleared");
	if (!(ft_roomlist(CLEAR, NULL)))
		ft_putendl("Roomlist cleared");
	//if (!(ft_pathlist(CLEAR, -1)))
	//	ft_putendl("Pathlist cleared");
	
	store_input(CLEAR);

	/*
	while (1);
		wait(&waiter);
*/		
	return (0);
}
