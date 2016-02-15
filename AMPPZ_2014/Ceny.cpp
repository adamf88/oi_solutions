#include <cstdio>
#include <vector>
#include <limits>
using namespace std;

int ceny[100][17];
int dojazd[100];
int all[1 << 16];

int cena(int h, int prod)
{
	if (prod == 0)
		return 0;

	int ret = dojazd[h];

	int pos = 0;
	while (prod)
	{
		if (prod & 1)
			ret += ceny[h][pos];
		prod /= 2;
		++pos;
	}

	return ret;
}

int main()
{
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; ++i)
	{
		scanf("%d", &dojazd[i]);
		for (int j = 0; j < m; ++j)
		{
			scanf("%d", &ceny[i][j]);
		}
	}
	
	int sets = 1 << m;
	vector<int> koszt;
	koszt.resize(sets + 1, numeric_limits<int>::max());
	koszt[0] = 0;

	for (int i = 0; i < sets; ++i)
		all[i] = std::numeric_limits<int>::max();

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < sets; ++j)
		{
			int cij = cena(i, j);
			int v = all[j];
			all[j] = cij < all[j] ? cij : all[j];
		}
	}

	for (int j = 0; j < sets; ++j) // zbior A
	{
		int A = j;
		int kosztA = koszt[A];

		int B = A;
		while (B > 0)
		{
			int D = A - B;
			int zakup = all[B] + koszt[D];
			kosztA = zakup < kosztA ? zakup : kosztA;
			B = (B - 1) & A;
		}

		koszt[j] = kosztA;
	}
	

	printf("%d\n", koszt[sets - 1]);
	return 0;
}