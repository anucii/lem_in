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

int		main(int ac, char **av)
{
	t_list	*stored_input = NULL;
	size_t	i = 0;
	int		waiter = 0;

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
	store_input(CLEAR);
	while (1)
		wait(&waiter);
	return (0);
}
