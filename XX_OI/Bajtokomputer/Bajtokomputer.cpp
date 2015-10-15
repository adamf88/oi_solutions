#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

#define nil 1000000000

int main()
{
	int n, x;
	int a[3], b[3];
	int* prevv = a;
	int* curr = b;

	scanf("%d", &n);
	scanf("%d", &x);
	
	prevv[0] = prevv[1] = prevv[2] = nil;
	prevv[x + 1] = 0;
	for (int i = 1; i < n; ++i)
	{
		scanf("%d", &x);

		curr[0] = prevv[0] + abs(x - (-1)); //idx = -1
		
		if (x == -1)
			curr[1] = nil;
		else if (x == 0)
			curr[1] = min(prevv[0], prevv[1]); //idx = 0
		else if (x == 1)
			curr[1] = prevv[0] + 1; //idx = 0
			
		if (x == 1)
			curr[2] = min(min(prevv[0], prevv[1]), prevv[2]); //idx: 1
		else
			curr[2] = prevv[2] + abs(x - 1);				  //idx: 1
		
		swap(prevv, curr);
	}

	int res = min(min(prevv[0], prevv[1]), prevv[2]);
	if (res < nil)
		printf("%d\n", res);
	else
		puts("BRAK");
	return 0;

}