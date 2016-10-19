#include "Knapsack.hpp"

Knapsack::Knapsack(int population_size, int limit, vector<int> values,
		vector<int> weights, double pc, double pm) :
		GA<bool>(population_size, weights.size(), pc, pm) {
	this->limit = limit;
	this->weights = weights;
	this->values = values;
}

bool Knapsack::mutate_gene(bool gene) {
	gene = !gene;
	return gene;
}

int Knapsack::fitness(Chromosome chromosome) {
	int weight = 0, value = 0;
	for (int i = 0; i < this->chromosome_size; i++)
		weight += chromosome[i] * weights[i], value += chromosome[i] * values[i];
	return (weight <= limit ? value : 0);
}

void Knapsack::initialize() {
	for (int i = 0; i < this->population.size(); i++) {
		this->population[i] = Chromosome(this->chromosome_size);
		for (int j = 0; j < this->chromosome_size; j++)
			this->population[i][j] = rand() % 2;
		this->fitness_value[i] = fitness(this->population[i]);
	}
}

void Knapsack::crossover() {
	// Single point crossover
	int r = 1 + rand() % (this->chromosome_size - 2);
	int p1 = this->parents.first;
	int p2 = this->parents.second;
	for (int i = 0; i < r; i++) {
		bool tmp = this->population[p1][i];
		this->population[p1][i] = this->population[p2][i];
		this->population[p2][i] = tmp;
		//swap(this->population[p1][i], this->population[p2][i]);
	}
}

int Knapsack::decode(Chromosome chromosome) {
	int val = 0;
	for (int i = 0; i < this->chromosome_size; i++) {
		val += chromosome[i] * (values[i]);
	}
	return val;
}
