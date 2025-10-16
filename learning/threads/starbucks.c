#include <stdio.h>
#include <unistd.h>

void	make_coffee(char *name)
{
	printf("Barista %s is making coffee...\n", name);
	sleep (3);
	printf("Coffee is ready!\n");
}

int	main(void)
{
	make_coffee("Luca");
	make_coffee("Paolo");
}
