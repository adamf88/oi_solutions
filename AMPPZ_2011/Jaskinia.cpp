#include <algorithm>
#include <iostream>
#include <vector>
#include <set>

using namespace std;
vector< vector<int> > t;
vector<int> krt, lens;
int n;

int nwd(int a, int b)
{
	int c;
	while (b != 0)
	{
		c = a % b;
		a = b;
		b = c;
	}
	return a;
}

int dfs(int parent, int v)
{
	int len = 1;
	for (int i = 0; i < t[v].size(); ++i)
	{
		if(parent != t[v][i])
			len += dfs(v, t[v][i]);
	}
	++lens[len];
	return len;
}

int main()
{
	scanf("%d", &n);
	t.resize(n+1);
	lens.resize(n + 1);
	krt.resize(n + 1);
	for (int i = 1; i <= n - 1; ++i)
	{
		int p;
		scanf("%d", &p);
		t[p].push_back(i + 1);
		t[i + 1].push_back(p);
	}

	dfs(1, 1);

	for (int i = 1; i < lens.size(); ++i)
	{
		if (lens[i])
		{
			int val = nwd(i, n - i);
			krt[val] += lens[i];
		}
	}

	for (int i = n; i > 1; --i)
	{
		if (n % i == 0)
		{
			int v = 0;
			for (int j = i; j <= n; j += i)
				v += krt[j];

			if (v == n / i)
				printf("%d ", n / i);
		}
	}
	printf("%d\n", n);
	return 0;
}