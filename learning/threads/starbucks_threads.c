#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void	*make_coffee(void *data)
{
		//Print which barista is preparing the drink
	printf("Barista preparing coffee\n");
		//Simulate the time taken to prepare a drink
	sleep (2);
		//Notify when the drink is ready
	printf("Coffee is ready!\n");
	return (NULL);
}

/*
int	main(void)
{
	pthread_t	barista1;
	pthread_t	barista2;

	pthread_create(&barista1, NULL, make_coffee, NULL);
	pthread_create(&barista2, NULL, make_coffee, NULL);
	
	pthread_join(barista1, NULL);
	pthread_join(barista2, NULL);
}
*/

int	main(void)
{
	pthread_t	baristas[500];

	for (int i = 0; i < 500; ++i)
	{
			//if successful, the pthread_create() function will return zero,
			//otherwise an error number will be returned to indicate the error
			//Si el valor de retorno es != de 0, ERROR
		if (pthread_create(baristas + i, NULL, make_coffee, NULL))
			exit(1);
	}
	for (int i = 0; i < 500; ++i)
	{
		printf("Identifier-> %lu\n", baristas[i]);
	}

	for (int i = 0; i < 500; ++i)
	{
		pthread_join(baristas[i], NULL);
	}
}
