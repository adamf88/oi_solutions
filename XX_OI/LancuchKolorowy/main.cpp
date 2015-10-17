#include <cstdio>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

vector<int> l;
vector<int> c;
vector<int> curr_count;
vector<int> des_count;
vector<int> colors;
int main()
{
	int n, m, t;
	long long length = 0;
	scanf("%d %d", &n, &m);
	curr_count.resize(n + 1);
	des_count.resize(n + 1);
	colors.reserve(n);

	l.reserve(m);
	c.reserve(m);
	for (int i = 0; i < m; ++i)
	{
		scanf("%d", &t);
		l.push_back(t);
		length += t;

		if (length > n)
		{
			puts("0");
			return 0;
		}
	}

	for (int i = 0; i < m; ++i)
	{
		scanf("%d", &t);
		c.push_back(t);
		des_count[t] = l[i];
	}

	int bad = c.size();
	int result = 0;
	for (int first = 0, last = 0; last < n; ++last)
	{
		int color;
		scanf("%d", &color);
		colors.push_back(color);
		int dst = des_count[color];
		if (dst == curr_count[color])
			++bad;
		++curr_count[color];
		if (dst == curr_count[color])
			--bad;

		if (last - first >= length - 1)
		{
			if (bad == 0)
				++result;

			int to_remove = colors[first];
			dst = des_count[to_remove];
			if (dst == curr_count[to_remove])
				++bad;
			--curr_count[to_remove];
			if (dst == curr_count[to_remove])
				--bad;

			++first;
		}
	}

	printf("%d\n", result);

	return 0;

}