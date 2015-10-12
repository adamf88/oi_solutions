#include <cstdio>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

typedef long long ll;

int main()
{
	ll m, d, n;
	vector<ll> fuel_level;
	scanf("%lld %lld %lld", &m, &d, &n);
	fuel_level.resize(n);
	for (int i = 0; i < n; ++i)
		scanf("%lld", &fuel_level[i]);

	sort(fuel_level.begin(), fuel_level.end());

	ll distance_needed = m - d; //dystan pomiedzy postojem taksowek a punktem koncowym
	//znajdujemy pierwsza taksowke ktora jest w stanie dojechac do konca i odkladamy ja na bok
	vector<ll>::iterator position = lower_bound(fuel_level.begin(), fuel_level.end(), distance_needed);

	//jesli nie znaleziono takiej to koniec
	if (position == fuel_level.end())
	{
		puts("0");
		return 0;
	}

	int result = 0;
	ll smallest = *position;
	//odlozna taksowka z tej pozycji jest w stanie dojechac do konca. Musimy dojechac tutaj pozostalymi.
	//Dodatkowo z poprzedniego warunku wiemy ze jestesmy nie dalej niz w punkcie d
	ll min_location = d - (smallest - (m - d)) / 2;
	ll current_position = 0;
	vector<ll>::iterator it = fuel_level.end() - 1;
	for (; it >= fuel_level.begin() && current_position < min_location; --it)
	{
		if (it == position) continue;
		
		ll fuel = *it;
		fuel -= d - current_position;
		if (fuel > 0)
		{
			current_position += fuel;
			++result;
		}
		else
			break;
	}

	if (current_position < min_location)
	{
		puts("0");
	}
	else if(current_position >= m)
	{
		printf("%d\n", result);
	}
	else
	{
		printf("%d\n", result + 1);
	}
	return 0;
}