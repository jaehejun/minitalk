#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

int	main(void)
{
	//static int	compare_pid;
	//static int	client_pid;

	//if (compare_pid <= 65536)
	//{
	//	if (compare_pid == 0)
	//		compare_pid = 1;
	//	if (signum == SIGUSR1)
	//		client_pid = client_pid | compare_pid;
	//	else if (signum == SIGUSR2)
	//		client_pid = client_pid & compare_pid;
	//	compare_pid = compare_pid << 1;
	//	printf("client_pid : %d\n", client_pid);
	//}
	//else if (compare_pid > 65536)
	//{
	//	receive_string(signum, client_pid);
	//}
	int	client_pid = 35988;
	int	compare_bit;

	compare_bit = 1;
	while (compare_bit <= 65536)
	{
		printf("Compare bit : %d\n", compare_bit);
		if ((client_pid & compare_bit))
			printf("1\n");
		else if ((client_pid & compare_bit) == 0)
			printf("0\n");
		usleep(1000);
		compare_bit = compare_bit << 1;
		printf("CLIENT PID : %d\n", client_pid);
	}
}
	//1000110010010100

	//printf("%d\n", compare_bit);
	//printf("%d\n", message & compare_bit);

	//compare_bit = (compare_bit << 1);
	//printf("%d\n", compare_bit);
	//printf("%d\n", message & compare_bit);
	//compare_bit = (compare_bit << 1);
	//printf("%d\n", compare_bit);
	//printf("%d\n", message & compare_bit);
	//compare_bit = (compare_bit << 1);
	//printf("%d\n", compare_bit);
	//printf("%d\n", message & compare_bit);
	//compare_bit = (compare_bit << 1);
	//printf("%d\n", compare_bit);
	//printf("%d\n", message & compare_bit);
	//compare_bit = (compare_bit << 1);
	//printf("%d\n", compare_bit);
	//printf("%d\n", message & compare_bit);

//	if (message & compare_bit)
//		printf("1\n");
//	else
//		printf("0\n");
//	compare_bit = compare_bit << 1;
//	printf("%d\n", compare_bit);

//	if (message & compare_bit)
//		printf("1\n");
//	else
//		printf("0\n");
//	compare_bit = compare_bit << 1;
//	printf("%d\n", compare_bit);
//}