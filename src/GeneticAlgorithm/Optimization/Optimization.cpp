#include "Optimization.h"

Chromosome Optimization::twoOpt(const Chromosome &chr) {
    std::vector<uint> optimizedGenes(chr.genes);
    uint genesSize = optimizedGenes.size();
    uint optimizedFitness = chr.fitness;
    for(uint i = 0; i < genesSize - 1; i++) {
        for(uint j = i + 2; j < genesSize; j++) {
            int oldCost = static_cast<int>(calcRouteCost(optimizedGenes, *chr.graph, i, j + 1));
            int newCost = static_cast<int>(calcTwoOptRouteCost(optimizedGenes, *chr.graph, i, j + 1));
            int deltaFitness = newCost - oldCost;
            if(deltaFitness < 0) {
                twoOptSwap(optimizedGenes, i + 1, j);
                optimizedFitness += deltaFitness;
            }
        }
    }
    Chromosome optimizedChr{optimizedGenes, chr.graph, optimizedFitness};
    return std::min(chr, optimizedChr);
}

void Optimization::twoOptSwap(std::vector<uint> &genes, uint i, uint j) {
    while(i < j) {
        std::swap(genes[i], genes[j]);
        i++;
        j--;
    }
}

uint Optimization::calcRouteCost(const std::vector<uint> &genes, const Graph &costSrc, uint i, uint j) {
    uint routeCost{0};
    uint genesSize = genes.size();
    while(i < j) {
        routeCost += costSrc.adjacencyMatrix[genes[i]][genes[(i + 1) % genesSize]];
        i++;
    }
    return routeCost;
}

uint Optimization::calcTwoOptRouteCost(const std::vector<uint> &genes, const Graph &costSrc, uint i, uint j) {
    uint routeCost{0};
    uint genesSize = genes.size();
    uint rangeBegin = i + 1;
    uint rangeEnd = j - 1;
    while(rangeEnd > rangeBegin) {
        routeCost += costSrc.adjacencyMatrix[genes[rangeEnd]][genes[rangeEnd - 1]];
        rangeEnd--;
    }
    routeCost += costSrc.adjacencyMatrix[genes[i]][genes[j - 1]];
    routeCost += costSrc.adjacencyMatrix[genes[i + 1]][genes[j % genesSize]];
    return routeCost;
}

Chromosome Optimization::hillClimbing(const Chromosome &chr) {
    Chromosome bestChromosome = chr;
    bool foundLocalExtrema{false};
    while(!foundLocalExtrema) {
        auto neighbors = openNeighbors(bestChromosome);
        if(neighbors.begin()->fitness >= bestChromosome.fitness) {
            foundLocalExtrema = true;
        } else {
            bestChromosome = *neighbors.begin();
        }
    }
    return bestChromosome;
}

std::set<Chromosome> Optimization::openNeighbors(Chromosome &chr) {
    uint genesSize = chr.genes.size();
    std::set<Chromosome> neighbors;
    for(uint i = 1; i < genesSize - 1; i++) {
        int initialFitness = static_cast<int>(calcRouteCost(chr.genes, *chr.graph, i - 1, i + 2));
        std::swap(chr.genes[i], chr.genes[i + 1]);
        int modifiedFitness = static_cast<int>(calcRouteCost(chr.genes, *chr.graph, i - 1, i + 2));
        int deltaFitness = modifiedFitness - initialFitness;
        neighbors.emplace(chr.genes, chr.graph, chr.fitness + deltaFitness);
        std::swap(chr.genes[i], chr.genes[i + 1]);
    }
    return neighbors;
}