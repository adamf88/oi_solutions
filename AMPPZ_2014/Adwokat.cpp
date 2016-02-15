#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

struct item
{
	item(int _s, int _e, int _id)
		: s(_s)
		, e(_e)
		, id(_id)
	{}
	int s;
	int e;
	int id;
};
vector< vector<item> > days;

struct Cmp
{
	bool operator()(const item& a, const item& b)
	{
		return a.e < b.e;
	}
};

int main()
{
	int n, m;
	scanf("%d %d", &n, &m);
	days.resize(m + 1);
	for (int i = 1; i <= n; ++i)
	{
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		days[c].push_back(item(a, b, i));
	}

	for (int i = 1; i < days.size(); ++i)
	{
		if (days[i].size() < 2)
		{
			puts("NIE");
			continue;
		}

		vector<item>::iterator it = std::min_element(days[i].begin(), days[i].end(), Cmp());

		int end_time = it->e;
		int end_id = it->id;

		int start2_id = -1;
		for (int j = 0; j < days[i].size(); ++j)
		{
			if (days[i][j].s > end_time)
			{
				start2_id = days[i][j].id;
				break;
			}
		}

		if (start2_id <= 0)
		{
			puts("NIE");
		}
		else
		{
			printf("TAK %d %d\n", end_id, start2_id);
		}
		
	}

	
	return 0;
}