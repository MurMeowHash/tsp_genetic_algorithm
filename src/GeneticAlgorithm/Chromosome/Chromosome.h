#pragma once

#include <vector>
#include "../../utils/utils.h"
#include "../../Graph/Graph.h"

struct Chromosome {
    std::vector<uint> genes;
    uint fitness;
    double inverseFitness;
    Graph *graph;
    Chromosome(const std::vector<uint> &genes, Graph *graph);
    Chromosome(const std::vector<uint> &genes, Graph *graph, uint fitness);
    bool operator<(const Chromosome &rhs) const;
    bool operator>(const Chromosome &rhs) const;
private:
    void calculateFitness();
    void calculateInverseFitness();
};