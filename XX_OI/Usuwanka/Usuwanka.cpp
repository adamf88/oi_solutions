#include <cstdio>
#include <vector>
#include <stack>
using namespace std;

char buffer[1000010];
vector<int> output;
vector<int> S, prefix_sum;

int topSum(int k)
{
	if (prefix_sum.size() <= k)
		return -1;
	return prefix_sum.back() - *(prefix_sum.end() - (k + 1));
}

int main()
{
	int n, k;
	char c;
	
	scanf("%d %d\n", &n, &k);
	scanf("%s", buffer);
	int elems = k + 1;
	S.reserve(n);
	output.reserve(n);
	prefix_sum.reserve(n);
	prefix_sum.push_back(0);
	for (int i = 0; i < n; ++i)
	{
		int value = buffer[i] == 'b' ? 1 : -k;
		S.push_back(i);
		prefix_sum.push_back(prefix_sum.back() + value);
		if (topSum(elems) == 0)
		{	//we found proper order - remove k elements
			output.insert(output.end(), S.rbegin(), S.rbegin() + elems);//copy to output, in reverse order
			S.resize(S.size() - elems);
			prefix_sum.resize(prefix_sum.size() - elems);
		}
	}

	for (int i = output.size() - 1, ile = 1; i >= 0; --i, ++ile)
	{
		printf("%d ", output[i] + 1);
		if (ile % elems == 0)
			puts("");
	}
}