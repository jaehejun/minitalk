#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int	main(void)
{
	int	number = 0;
	int	bit = 0;
	//while (bit <= 65536)
	//{
	//	printf("Compare bit : %d\n", bit);
	//	if ((number & bit) == bit)
	//		printf("1\n");
	//	else if ((number & bit) == 0)
	//		printf("0\n");
	//	bit = bit << 1;
	//	printf("CLIENT PID : %d\n", number);
	//}
	number = number & ~(1 << bit);
	number = number | (1 << bit);
	bit++;
	printf("number : %d\n", number);
	number = number & ~(1 << bit);
	number = number | (1 << bit);
	bit++;
	printf("number : %d\n", number);
	number = number & ~(1 << bit);
	number = number | (1 << bit);
	bit++;
	printf("number : %d\n", number);
	number = number & ~(1 << bit);
	number = number | (1 << bit);
	bit++;
	printf("number : %d\n", number);
	return (0);
}

0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789