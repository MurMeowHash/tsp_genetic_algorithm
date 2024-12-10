#pragma once

#include "../Chromosome/Chromosome.h"
#include "../../utils/utils.h"
#include <unordered_map>
#include <unordered_set>

class Crossover {
private:
    static void insertGen(uint &targetGen, uint srcGen, const std::unordered_map<uint, uint> &mapping);
    static void insertGen(uint &targetGen, uint srcGen, const std::unordered_set<uint> &selectedGenes,
                          const Chromosome &oppositeChr, auto &offspringPosIterator);
    static void insertGen(uint &targetGen, const Chromosome &priorChr, const Chromosome &sideChr,
                          uint &priorChrIndex, uint &sideChrIndex, std::vector<bool> &genesInPath);
public:
     NODISCARD static Chromosome partiallyMappedCrossover(const Chromosome &lhs, const Chromosome &rhs);
     NODISCARD static Chromosome orderBasedCrossover(const Chromosome &lhs, const Chromosome &rhs);
     NODISCARD static Chromosome alternatingPositionCrossover(const Chromosome &lhs, const Chromosome &rhs);
};