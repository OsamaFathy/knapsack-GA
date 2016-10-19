#ifndef GA_HPP_
#define GA_HPP_
#include <vector>
#include <algorithm>
#include <stdlib.h>
using namespace std;

template<class GeneType>
class GA {

protected:
	typedef vector<GeneType> Chromosome;
	int chromosome_size;
	double pc, pm;
	vector<Chromosome> population;
	vector<int> fitness_value;
	pair<int, int> parents;
	virtual void initialize() = 0;
	virtual int fitness(Chromosome chromosome) = 0;
	void selection();
	virtual void crossover() = 0;
	void mutation(Chromosome& chromosome);
	virtual GeneType mutate_gene(GeneType gene) = 0;
	virtual int decode(Chromosome chromosome) = 0; //assuming the solution is always int because I'm lazy

public:
	GA(int population_size, int chromosome_size, double pc, double pm);
	int run();
};

template<class GeneType>
GA<GeneType>::GA(int population_size, int chromosome_size, double pc, double pm) {
	population.resize(population_size);
	fitness_value.resize(population_size);
	this->chromosome_size = chromosome_size;
	this->pc = pc;
	this->pm = pm;
}

template<class GeneType>
void GA<GeneType>::mutation(Chromosome& chromosome) {
	int gene_index = rand() % chromosome_size;
	chromosome[gene_index] = mutate_gene(chromosome[gene_index]);
	fitness_value[gene_index] = fitness(chromosome);
}

template<class GeneType>
void GA<GeneType>::selection() {
	int pop_sz = population.size();
	int cummulative[pop_sz];
	for (int i = 0; i < pop_sz; i++) {
		cummulative[i] = bool(i) * cummulative[i - 1] + fitness_value[i];
	}

	int rand1 = rand() % cummulative[pop_sz - 1];
	int gene1 = upper_bound(cummulative, cummulative + pop_sz, rand1) - cummulative;

	int rand2 = rand() % (cummulative[pop_sz - 1] - fitness_value[gene1]);
	if(rand2 < cummulative[gene1] && (!gene1 || rand2 >= cummulative[gene1]))
		rand2 += fitness_value[gene1];
	int gene2 = upper_bound(cummulative, cummulative + pop_sz, rand2) - cummulative;

	parents = {gene1, gene2};
}

template<class GeneType>
int GA<GeneType>::run() {
	initialize();
	for (int i = 0; i < 100000; i++) {
		double r1 = rand() / (double) RAND_MAX;
		double r2 = rand() / (double) RAND_MAX;
		double r3 = rand() / (double) RAND_MAX;
		selection();
		if (r1 < pc)
			crossover();
		if (r2 < pm) {
			mutation(population[parents.first]);
		}
		if (r3 < pm) {
			mutation(population[parents.second]);
		}
	}
	int mx = 0;
	for (int i = 0; i < population.size(); i++)
		mx = max(mx, fitness_value[i]);
	return mx;
}

#endif /* GA_HPP_ */
