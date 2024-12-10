#include "GeneticAlgorithm.h"
#include <numeric>
#include <algorithm>
#include "../Random/Random.h"
#include <iostream>

GeneticAlgorithm::GeneticAlgorithm(Graph &graph)
: graph{graph}, probabilities(POPULATION_SIZE), solutionResult{nullptr} {

}

void GeneticAlgorithm::operator()(uint maxGenerations, const uint *satisfactoryFitness,
                                  const std::function<Chromosome(const Chromosome &, const Chromosome &)> &crossover,
                                  const std::function<Chromosome(const Chromosome &)> &mutation,
                                  const std::function<Chromosome(const Chromosome &)> &optimization) {
    delete solutionResult;
    uint optimizationIteration{maxGenerations / OPTIMIZATION_PART};
    createInitialPopulation();
    bool reachedDesiredFitness{false};
    uint i{0};
    while(i < maxGenerations
          && !reachedDesiredFitness) {
        const Chromosome *firstParent, *secondParent;
        selectParents(firstParent, secondParent);
        Chromosome bestOffspring = crossover(*firstParent, *secondParent);
        if(Random::genProbability() <= MUTATION_PROBABILITY) {
            Chromosome mutatedOffspring = mutation(bestOffspring);
            if(mutatedOffspring.fitness < bestOffspring.fitness) {
                bestOffspring = mutatedOffspring;
            }
        }
        if(i >= optimizationIteration
        && i % OPTIMIZATION_FREQUENCY == 0) {
            Chromosome optimizedOffspring = optimization(bestOffspring);
            if(optimizedOffspring.fitness < bestOffspring.fitness) {
                bestOffspring = optimizedOffspring;
            }
        }
        auto worstChromosome = population.begin();
        if(bestOffspring.fitness <= worstChromosome->fitness) {
            population.erase(worstChromosome);
            population.insert(bestOffspring);
        }
        if(satisfactoryFitness) {
            reachedDesiredFitness = population.rbegin()->fitness <= *satisfactoryFitness;
        }
        i++;
        std::cout << "Best fitness: " << population.rbegin()->fitness << '\n';
    }
    solutionResult = new Chromosome{*population.rbegin()};
    population.clear();
}

void GeneticAlgorithm::createInitialPopulation() {
    std::vector<uint> genes(graph.getSize());
    for(uint i = 0; i < POPULATION_SIZE; i++) {
        std::iota(genes.begin(), genes.end(), 0);
        std::shuffle(genes.begin(), genes.end(), Random::getGenerator());
        Chromosome chr{genes, &graph};
        population.emplace(chr);
    }
}

void GeneticAlgorithm::calculatePopulationProbabilities() {
    double sharedFitness{0.0};
    for(auto &chromosome : population) {
        sharedFitness += chromosome.inverseFitness;
    }
    double currentProbability{0.0};
    uint i{0};
    for(auto &chromosome : population) {
        currentProbability += chromosome.inverseFitness / sharedFitness;
        probabilities[i++] = currentProbability;
    }
}

void GeneticAlgorithm::findParent(std::multiset<Chromosome, std::greater<>>::iterator &parentIterator) const {
    parentIterator = population.begin();
    double probability = Random::genProbability();
    int i{0};
    bool foundParent{false};
    while(i < probabilities.size()
          && !foundParent) {
        if(probability <= probabilities[i]) {
            foundParent = true;
        } else {
            parentIterator++;
            i++;
        }
    }
}

void GeneticAlgorithm::selectParents(const Chromosome *&firstParent, const Chromosome *&secondParent) {
    calculatePopulationProbabilities();
    decltype(population)::iterator firstParentIterator, secondParentIterator;
    findParent(firstParentIterator);
    auto omittedParent = population.extract(firstParentIterator);
    calculatePopulationProbabilities();
    findParent(secondParentIterator);
    population.insert(std::move(omittedParent));
    firstParent = &(*firstParentIterator);
    secondParent = &(*secondParentIterator);
}

GeneticAlgorithm::~GeneticAlgorithm() {
    delete solutionResult;
}

uint GeneticAlgorithm::getPath(std::vector<uint> &path) {
    if(solutionResult == nullptr) {
        return 0;
    }
    path = solutionResult->genes;
    return solutionResult->fitness;
}