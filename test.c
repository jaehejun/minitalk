#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

int	main(void)
{
	int				compare_bit;
	unsigned char	message;

	message = 107;
	printf("%c\n", message);

	compare_bit = 1;
	while (compare_bit <= 128)
	{
		if (message & compare_bit)
		{
			printf("1\n");
		}
		else
			printf("0\n");
		compare_bit = (compare_bit << 1);
		printf("%d\n", compare_bit);
	}
}
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