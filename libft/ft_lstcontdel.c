#include "libft.h"

void	ft_lstcontdel(void *cont, size_t size)
{
	ft_memdel(&cont);
	size = 0;
}
