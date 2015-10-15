#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

#define BUF_SIZE 4000
char bufor[BUF_SIZE + 1 + 30];
char *buf_pointer;
char *end_pointer;

bool end_of_buffer()
{
	return buf_pointer == end_pointer;
}

void init()
{
	buf_pointer = bufor;
	int readed = fread(bufor, 1, BUF_SIZE, stdin);
	end_pointer = bufor + readed;

	if (readed)
	{
		--end_pointer;

		//read last number to end
		while ((*end_pointer & 16) && readed)
		{
			++end_pointer;
			readed = fread(end_pointer, 1, 1, stdin);
		}

		if (*end_pointer & 16)
		{
			++end_pointer;
			*end_pointer = ' ';
		}

		//read white spaces 
		for (; (*buf_pointer & 16) == false;)
		{
			++buf_pointer;
			if (buf_pointer >= end_pointer)
			{
				init();
			}
		}
	}
}

void read_int(unsigned& l)
{
	char *data = buf_pointer;

	if (end_of_buffer())
		return;

	l = 0;

	while (*data & 16)
	{
		l *= 10;
		l += *data & 15; //-40
		++data;
	}

	//read white spaces 
	for (; (*data & 16) == false;)
	{
		++data;
		if (data >= end_pointer)
		{
			init();
			data = buf_pointer;
		}
	}

	buf_pointer = data;
}


vector<vector<int> > roads;

int check(int v, int k, int parent)
{
	int result = 0;
	for (int i = 0; i < roads[v].size(); ++i)
	{
		int u = roads[v][i];
		if (u != parent)
			result += check(u, k, v) + 1;
	}

	return max(0, result - k);
}

int main()
{
	init();
	unsigned n;
	read_int(n);
	roads.resize(n + 1);
	for (int i = 0; i < n - 1; ++i)
	{
		unsigned a, b;
		read_int(a);
		read_int(b);
		roads[a].push_back(b);
		roads[b].push_back(a);
	}

	int start = 0;
	int end = n;
	while (start < end)
	{
		int current = (start + end) / 2;
		int rest = check(1, current, -1);
		if (rest)
			start = current + 1;
		else
			end = current;

	}

	printf("%d\n", end);

	return 0;
}