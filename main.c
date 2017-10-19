#include "malloc.h"
#define META_SIZE sizeof(t_block)

int 	main(int ac, char **av)
{
	int i;
	void *test;
	void *free_test[200];

	i = 0;
	if(ac == 2)
	{
		while (i < 300)
		{
			if (i >= 1 && i < 200)
				free_test[i] = malloc(atoi(av[1]));
			else
				test = malloc(atoi(av[1]));
			i++;
		}
	}
	ft_printtab();
	ft_print();
	printf("\n==========FREE=========\n");
	i = 0;
	while (i < 200)
	{
		// if (free_test[i] )
		if (free_test[i] && i > 8 && i <102)
			free(free_test[i]);
			// free1(free_test[i]);
		i++;
	}
	ft_print();
	// ft_printtab();
	ft_munmap();
	ft_printtab();
	printf("\nrealloc \n");
	test = realloc(free_test[21], 1);
	ft_printtab();
	printf("\ntaille de la structure ===> %lu + %lu\n", META_SIZE, TINY*100);
	return (0);
}
