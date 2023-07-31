#include <stdio.h>

int	main(void)
{
	char	num = 33;
	char	result =  num << 2;
	int		i = 1, j = 1;

	printf("이동 전 : %d\n", num);
	while (i < 256)
	{
		if (num & 128/i)
			printf("%d번째 비트 : 1\n", j);
		else
			printf("%d번째 비트 : 0\n", j);
		i *= 2;
		j++;
	}
	printf("2칸 이동 결과 : %d\n", result);
	i = 1, j = 1;
	while (i < 256)
	{
		if (result & 128/i)
			printf("%d번째 비트 : 1\n", j);
		else
			printf("%d번째 비트 : 0\n", j);
		i *= 2;
		j++;
	}
}