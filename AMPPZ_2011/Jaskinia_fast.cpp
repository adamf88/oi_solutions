#include <algorithm>
#include <iostream>
#include <vector>
#include <set>

using namespace std;


#define BUF_SIZE 400
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



struct elem
{
	elem()
	: parent(0)
	, size(1)
	, childs(0)
	, childs_tp(0)
	{}

	elem* parent;
	int childs;
	int childs_tp;
	int size;
	int id;
};
vector<elem> t;
vector<int> krt, lens;
unsigned n;

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

#define FAST_READ 1

int main()
{

#ifdef FAST_READ
	init();
	read_int(n);
#else
	scanf("%d", &n);
#endif
	t.resize(n + 1);
	lens.resize(n + 1);
	krt.resize(n + 1);
	for (int i = 1; i <= n - 1; ++i)
	{
		unsigned p;
#ifdef FAST_READ
		read_int(p);
#else
		scanf("%u", &p);
#endif
		t[i].id = i;
		t[i+1].parent = &t[p];
		t[p].childs++;
		t[p].childs_tp++;

	}

	//computer tree sizes
	for (int i = 1; i <= n; ++i)
	{
		if (t[i].childs == 0)
		{
			int tree_size = t[i].size;
			elem* e = &t[i];
			while (e->parent)
			{
				e = e->parent;
				e->size += tree_size;
				tree_size = e->size;
				--(e->childs_tp);
				if (e->childs_tp)
					break;
			}
		}
	}

	//count amount of tree sizes
	for (int i = 1; i <= n; ++i)
		lens[t[i].size]++;

	//count nwd for each tree size
	for (int i = 1; i < lens.size(); ++i)
	{
		if (lens[i])
		{
			int val = nwd(i, n - i);
			krt[val] += lens[i];
		}
	}

	//count result
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