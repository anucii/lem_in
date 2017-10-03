#include "lem_in.h"

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

int		main(void)
{
	t_list	*stored_input = NULL;

	get_input();
	stored_input = store_input(READ);
	ft_printf("Input stored at %p\n", stored_input);
	t_display(stored_input);
	return (0);
}
