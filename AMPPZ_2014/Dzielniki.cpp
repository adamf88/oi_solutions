#include <cstdio>

int v[2000001];
int cnt[2000001];
int main()
{
	int n;
	int m = 0;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i)
	{
		int l;
		scanf("%d", &l);
		v[i] = l;
		++cnt[l];
		if (l > m)
			m = l;
	}

	unsigned long long result = 0;
	
	for (int i = 1; i <= m; ++i)
	{
		unsigned long long c = cnt[i];
		if (c)
		{
			result += c * (c - 1);
			for (int j = 2 * i; j <= m; j += i)
			{
				if(cnt[j])
					result += c * cnt[j];
			}
		}
	}

	printf("%llu\n", result);

	return 0;
}