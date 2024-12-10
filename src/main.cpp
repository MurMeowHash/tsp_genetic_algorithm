#include <iostream>
#include "Graph/Graph.h"
#include "GeneticAlgorithm/GeneticAlgorithm.h"
#include "GeneticAlgorithm/Crossover/Crossover.h"
#include "GeneticAlgorithm/Mutation/Mutation.h"
#include "GeneticAlgorithm/Optimization/Optimization.h"

void printResults(const std::vector<uint> &path, uint pathCost);

int main() {
    auto graph = new Graph{300, 5, 150};
    GeneticAlgorithm solver{*graph};
    solver(10000, nullptr,
           &Crossover::partiallyMappedCrossover,
           &Mutation::insertionMutation,
           &Optimization::twoOpt);
    std::vector<uint> path;
    uint pathCost = solver.getPath(path);
    printResults(path, pathCost);
    delete graph;
    return 0;
}

void printResults(const std::vector<uint> &path, uint pathCost) {
    std::cout << "\n\nPath: ";
    for(uint node : path) {
        std::cout << node << " -> ";
    }
    std::cout << *path.begin() << "\n\n";
    std::cout << "Cost: " << pathCost << '\n';
}