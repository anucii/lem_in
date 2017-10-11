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

void	t_rooms(void)
{
	t_list	*roomlist;
	char 	*user = "";

	roomlist = ft_roomlist(INIT, NULL);
	ft_putendl("Type \"all\" to show all rooms, or a specific name to show one");
	ft_putendl("Type \"STOP\" to stop the process");
	while (user && (ft_strcmp(user, "STOP")))
	{
		scanf(" %s", user);
		ft_roomlist(READ, user);
		ft_putendl("");
	}
	ft_printf("\nRooms list recap:\n");
	ft_roomlist(READ, NULL);
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
