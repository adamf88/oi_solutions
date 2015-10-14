#include <cstdio>
#include <vector>
using namespace std;
struct Solution
{
	short odd;
	short even;
};

vector<vector<short> > graph;
vector<bool> solved;

vector<vector<Solution> > solutions;

//global to avoid memory reallocations
vector<short> curLevel;
vector<short> nextLevel;

bool visitate(vector<Solution>& visit, int dest, int length)
{
	if (length % 2 == 0)
	{
		if (visit[dest].even > 0)
			return false;
		visit[dest].even = length;
	}
	else
	{
		if (visit[dest].odd > 0)
			return false;
		visit[dest].odd = length;
	}
	return true;
}

void solve(int start)
{
	solutions[start].resize(graph.size());
	solved[start] = true;
	vector<Solution>& visited = solutions[start];

	curLevel.clear();
	nextLevel.clear();

	nextLevel.push_back(start);
	int curLength = 0;
	while (nextLevel.size())
	{
		++curLength;
		curLevel.swap(nextLevel);
		nextLevel.clear();
		while (curLevel.size())
		{
			int elem = curLevel.back();
			curLevel.pop_back();

			for (int i = 0; i < graph[elem].size(); ++i)
			{
				int dest = graph[elem][i];
				if (visitate(visited, dest, curLength)) //if now added
				{
					nextLevel.push_back(dest); //we will visit it in next level
				}
			}
		}
	}
}

void show_result(int start, int end, int length)
{
	if (solutions[start].size() == 0)
	{
		puts("NIE");
		return;
	}

	int shortestLength = (length % 2 == 0) ? solutions[start][end].even : solutions[start][end].odd;
	if (shortestLength > 0 && shortestLength <= length)
		puts("TAK");
	else
		puts("NIE");
}

int main()
{
	int n, m, k;
	scanf("%d %d %d", &n, &m, &k);

	graph.resize(n + 1);
	solved.resize(n + 1);
	solutions.resize(n + 1);
	for (int i = 0; i < m; ++i)
	{
		int a, b;
		scanf("%d %d", &a, &b);
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	for (int i = 1; i <= n; ++i)
	{
		if (graph[i].size() == 0)
			solved[i] = true;
	}

	for (int i = 0; i < k; ++i)
	{
		int s, t, d;
		scanf("%d %d %d", &s, &t, &d);

		if (!solved[s] && !solved[t])
			solve(s);

		if (solved[s])
		{
			show_result(s, t, d);
		}
		else if (solved[t])
		{
			show_result(t, s, d);
		}
	}
	return 0;
}
