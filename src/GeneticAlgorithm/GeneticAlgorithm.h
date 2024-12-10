#pragma once

#include "../Graph/Graph.h"
#include "Chromosome/Chromosome.h"
#include "Crossover/Crossover.h"
#include "Mutation/Mutation.h"
#include "Optimization/Optimization.h"
#include <set>
#include <functional>

struct GeneticAlgorithm {
    friend class Crossover;
    friend class Mutation;
    explicit GeneticAlgorithm(Graph &graph);
    void operator()(uint maxGenerations, const uint *satisfactoryFitness,
                    const std::function<Chromosome(const Chromosome &, const Chromosome &)> &crossover,
                    const std::function<Chromosome(const Chromosome &)> &mutation,
                    const std::function<Chromosome(const Chromosome &)> &optimization);
    uint getPath(std::vector<uint> &path);
    ~GeneticAlgorithm();
private:
    static constexpr uint POPULATION_SIZE{50};
    static constexpr double MUTATION_PROBABILITY{0.1};
    static constexpr uint OPTIMIZATION_PART{4};
    static constexpr uint OPTIMIZATION_FREQUENCY{200};
    Graph &graph;
    std::multiset<Chromosome, std::greater<>> population;
    std::vector<double> probabilities;
    Chromosome *solutionResult;
    void createInitialPopulation();
    void calculatePopulationProbabilities();
    void findParent(std::multiset<Chromosome, std::greater<>>::iterator &parentIterator) const;
    void selectParents(const Chromosome *&firstParent, const Chromosome *&secondParent);
};