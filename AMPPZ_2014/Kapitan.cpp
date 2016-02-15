#include <cstdio>
#include <set>
#include <algorithm>
#include <vector>
#include <limits>

using namespace std;

struct target
{
	target()
		: n(0)
		, cost(0)
	{}

	target(int _n, int _cost)
		: n(_n)
		, cost(_cost)	
	{}

	int n;
	int cost;
};

struct node
{
	node()
		: value(numeric_limits<int>::max())
	{}

	vector<target> E;
	int value;
};

vector< node > G;

struct Cmp
{
	bool operator()(const int a, const int b)
	{
		if(G[a].value != G[b].value)
			return G[a].value < G[b].value;
		return a < b;
	}
};

void Dijkstra(int N)
{
	vector<bool> in_set;
	in_set.resize(G.size());

	set < int, Cmp > kopiec;
	kopiec.insert(N);
	
	G[N].value = 0;

	while (!kopiec.empty())
	{
		int v = *kopiec.begin();
		kopiec.erase(kopiec.begin());
		in_set[v] = false;

		int waga = G[v].value;
		for (int i = 0; i < G[v].E.size(); ++i)
		{
			int koszt = G[v].E[i].cost;
			int dest = G[v].E[i].n;
			if (waga + koszt < G[dest].value)
			{
				if (in_set[dest])
				{
					kopiec.erase(kopiec.find(dest));
				}
				in_set[dest] = true;
				G[dest].value = waga + koszt;
				kopiec.insert(dest);
			}
		}
	}
}

struct wyspa
{
	wyspa() {}
	wyspa(int _x, int _y, int _id)
		: x(_x)
		, y(_y)
		, id(_id)
	{}

	int x;
	int y;
	int id;
};

struct WyspaCmpX
{
	bool operator()(const wyspa& a, const wyspa& b)
	{
		return a.x < b.x;
	}
};

struct WyspaCmpY
{
	bool operator()(const wyspa& a, const wyspa& b)
	{
		return a.y < b.y;
	}
};

int dist(const wyspa& a, const wyspa &b)
{
	return min(abs(a.x - b.x), abs(a.y - b.y));
}

void FillGraph(vector<wyspa>& w)
{
	for (int i = 0; i < w.size(); ++i)
	{
		if (i > 0)
		{
			int d = dist(w[i], w[i - 1]);
			G[w[i].id].E.push_back(target(w[i - 1].id, d));
		}
		if (i < w.size() - 1)
		{
			int d = dist(w[i], w[i + 1]);
			G[w[i].id].E.push_back(target(w[i + 1].id, d));
		}
	}
}

int main()
{
	int n;
	vector<wyspa> wyspy;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
	{
		int x, y;
		scanf("%d %d", &x, &y);
		wyspy.push_back(wyspa(x, y, i));
	}
	
	G.resize(wyspy.size() + 1);
	sort(wyspy.begin(), wyspy.end(), WyspaCmpX());
	FillGraph(wyspy);
	sort(wyspy.begin(), wyspy.end(), WyspaCmpY());
	FillGraph(wyspy);

	Dijkstra(1);
	printf("%d\n", G[wyspy.size()].value);
}