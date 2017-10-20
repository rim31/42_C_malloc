#include "../includes/malloc.h"

void		show(void *p)
{
	ft_putstr("0x");
	ft_putnbr_base((intmax_t)p, 16);
}

void		display_p_and_p(void *p1, void *p2, size_t size)
{
	display_p(p1);
	ft_putstr(" - ");
	display_p(p2);
	ft_putstr(" : ");
	ft_putnbr(size);
	ft_putstr(" octets\n");
}

void		display_str_and_p(char *str, void *p)
{
	ft_putstr(str);
	ft_putstr(": ");
	if (p == NULL)
		ft_putstr("No zone");
	else
		display_p(p);
	ft_putstr("\n");
}

size_t		show_alloc_page(t_block *cur, char *zone)
{
	t_block	*tmp;
	size_t	count;

	count = 0;
	tmp = cur;
	if (tmp != NULL)
		display_str_and_p(zone, tmp);
	else
	{
		display_str_and_p(zone, NULL);
		return (0);
	}
	while (tmp)
	{
		if (tmp->is_free == 0)
		{
			display_p_and_p((tmp + BLOCK_SIZEOF),
			(tmp + tmp->size + BLOCK_SIZEOF), tmp->size);
			count += tmp->size;
		}
		tmp = tmp->next;
	}
	return (count);
}

void		show_alloc_mem(void)
{
	size_t	count;

	count = 0;
	pthread_mutex_lock(&g_malloc_lock);
	count += show_alloc_page(g_page.tiny, "TINY");
	count += show_alloc_page(g_page.small, "SMALL");
	count += show_alloc_page(g_page.large, "LARGE");
	ft_putstr("Total: ");
	ft_putnbr(count);
	ft_putstr("\n");
	pthread_mutex_unlock(&g_malloc_lock);
}
