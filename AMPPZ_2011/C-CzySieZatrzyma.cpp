#include <stdio.h>

int main()
{
	unsigned long long n;
	scanf("%llu", &n);

	if ((n & (n - 1)) == 0)
		puts("TAK");
	else
		puts("NIE");
	return 0;
}