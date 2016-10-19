#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>

#include "Knapsack.h"
using namespace std;

int iterations_count = 10000;
int population_size = 10000;
double pc = 0.3;
double pm = 0.07;

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

		Knapsack test(iterations_count, population_size, limit, values, weights, pc,
				pm);
		cout << "Case " << f << ": " << test.run() << endl;
	}
	return 0;
}
