#include <stdio.h>

int	main(void)
{
	int	a;
	int	b;
	int	c;

	a = 178;
	b = 104;
	c = 10;

	printf("%d & %d = %d\n", a, b, a & b);
	printf("%d | %d = %d\n", a, b, a | b);
	printf("c = %d ^ %d = %d\n", a, b, a ^ b);
	printf("c = %d, ~c = %d\n", c, ~c);
}