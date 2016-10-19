#include "Knapsack.hpp"
#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>
using namespace std;

int main() {
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);

	srand(time(NULL));
	int n;
	cin >> n;
	for (int f = 1; f <= n; f++) {
		int num, limit;
		cin >> num >> limit;
		vector<int> weights(num);
		vector<int> values(num);
		for (int i = 0; i < num; i++)
			cin >> weights[i] >> values[i];

		Knapsack test(1000, limit, values, weights, 0.5, 0.6);
		cout << "Case " << f << ": " << test.run() << endl;
	}
	return 0;
}
