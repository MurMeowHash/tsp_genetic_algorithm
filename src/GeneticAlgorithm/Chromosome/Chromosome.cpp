#include "Chromosome.h"

Chromosome::Chromosome(const std::vector<uint> &genes, Graph *graph)
: genes(genes), graph{graph}, fitness{0} {
    calculateFitness();
}

Chromosome::Chromosome(const std::vector<uint> &genes, Graph *graph, uint fitness)
: genes(genes), graph{graph}, fitness{fitness} {
    calculateInverseFitness();
}

void Chromosome::calculateFitness() {
    uint genesLastIndex = genes.size() - 1;
    for(uint i = 0; i < genesLastIndex; i++) {
        fitness += graph->adjacencyMatrix[genes[i]][genes[i + 1]];
    }
    fitness += graph->adjacencyMatrix[genes[genesLastIndex]][genes[0]];
    calculateInverseFitness();
}

bool Chromosome::operator<(const Chromosome &rhs) const {
    return fitness < rhs.fitness;
}

bool Chromosome::operator>(const Chromosome &rhs) const {
    return fitness > rhs.fitness;
}

void Chromosome::calculateInverseFitness() {
    if(fitness == 0) {
        return;
    }
    inverseFitness = 1.0 / static_cast<double>(fitness);
}