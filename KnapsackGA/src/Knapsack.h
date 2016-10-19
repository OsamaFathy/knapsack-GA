#ifndef KNAPSACK_HPP_
#define KNAPSACK_HPP_

#include <bits/stdc++.h>
#include "GA.hpp"

class Knapsack: public GA<bool> {

private:
	vector<int> weights;
	vector<int> values;
	int limit;
	bool mutate_gene(bool);
	int decode(Chromosome);
	int fitness(Chromosome);
	void crossover();
	void initialize();

public:
	Knapsack(int population_size, int limit, vector<int> values,
			vector<int> weights, double pc, double pm);
};

#endif
