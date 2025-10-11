#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/wait.h>

//the ledger is a shared resource
uint64_t	ledger = 0;

int	main(void)
{
	pid_t	pid;

	pid = fork();
	//child
	if (pid == 0)
	{
		ledger += 42;
		printf("child ledger-> %lu\n", ledger);
	}
	//father
	else
	{
		ledger += 42;
		wait(NULL);
		printf("father ledger-> %lu\n", ledger);
	}
}
