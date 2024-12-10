#include "Crossover.h"
#include "../../Random/Random.h"
#include <algorithm>
#include <set>
#include <array>
#include "../../Range/Range.h"

Chromosome Crossover::partiallyMappedCrossover(const Chromosome &lhs, const Chromosome &rhs) {
    uint startCutOff, endCutOff;
    Range::cutPart(lhs.genes.size(), startCutOff, endCutOff);
    uint mappingSize = endCutOff - startCutOff + 1;
    std::unordered_map<uint, uint> firstOffspringMappings, secondOffspringMappings;
    std::vector<uint> firstOffspringGenes(lhs.genes.size()), secondOffspringGenes(lhs.genes.size());
    firstOffspringMappings.reserve(mappingSize);
    secondOffspringMappings.reserve(mappingSize);
    for(uint i = startCutOff; i <= endCutOff; i++) {
        firstOffspringGenes[i] = rhs.genes[i];
        secondOffspringGenes[i] = lhs.genes[i];
        firstOffspringMappings[rhs.genes[i]] = lhs.genes[i];
        secondOffspringMappings[lhs.genes[i]] = rhs.genes[i];
    }
    for(uint i = 0; i < startCutOff; i++) {
        insertGen(firstOffspringGenes[i], lhs.genes[i], firstOffspringMappings);
        insertGen(secondOffspringGenes[i], rhs.genes[i], secondOffspringMappings);
    }
    for(uint i = endCutOff + 1; i < firstOffspringGenes.size(); i++) {
        insertGen(firstOffspringGenes[i], lhs.genes[i], firstOffspringMappings);
        insertGen(secondOffspringGenes[i], rhs.genes[i], secondOffspringMappings);
    }
    Chromosome firstOffspring{firstOffspringGenes, rhs.graph};
    Chromosome secondOffspring{secondOffspringGenes, lhs.graph};
    return std::min(firstOffspring, secondOffspring);
}

void Crossover::insertGen(uint &targetGen, uint srcGen, const std::unordered_map<uint, uint> &mapping) {
    bool inserted{false};
    while(!inserted) {
        if(mapping.contains(srcGen)) {
            srcGen = mapping.at(srcGen);
        } else {
            targetGen = srcGen;
            inserted = true;
        }
    }
}

Chromosome Crossover::orderBasedCrossover(const Chromosome &lhs, const Chromosome &rhs) {
    uint genesSize = lhs.genes.size();
    uint positionsCount = Random::iRange(1u, static_cast<uint>(genesSize));
    std::unordered_set<uint> firstSelectedGenes, secondSelectedGenes;
    std::set<uint> selectedPositions;
    firstSelectedGenes.reserve(positionsCount);
    secondSelectedGenes.reserve(positionsCount);
    for(uint i = 0; i < positionsCount; i++) {
        uint position = Random::iRange(0u, genesSize - 1);
        if(!selectedPositions.contains(position)) {
            selectedPositions.emplace(position);
            firstSelectedGenes.emplace(rhs.genes[position]);
            secondSelectedGenes.emplace(lhs.genes[position]);
        }
    }
    std::vector<uint> firstOffspringGenes(genesSize), secondOffspringGenes(genesSize);
    auto firstOffspringPosIterator = selectedPositions.begin();
    auto secondOffspringPosIterator = selectedPositions.begin();
    for(uint i = 0; i < genesSize; i++) {
        insertGen(firstOffspringGenes[i], lhs.genes[i], firstSelectedGenes,
                  rhs, firstOffspringPosIterator);
        insertGen(secondOffspringGenes[i], rhs.genes[i], secondSelectedGenes,
                  lhs, secondOffspringPosIterator);
    }
    Chromosome firstOffspring{firstOffspringGenes, lhs.graph};
    Chromosome secondOffspring{secondOffspringGenes, rhs.graph};
    return std::min(firstOffspring, secondOffspring);
}

void Crossover::insertGen(uint &targetGen, uint srcGen, const std::unordered_set<uint> &selectedGenes,
                          const Chromosome &oppositeChr, auto &offspringPosIterator) {
    if(selectedGenes.contains(srcGen)) {
        targetGen = oppositeChr.genes[*offspringPosIterator++];
    } else {
        targetGen = srcGen;
    }
}

Chromosome Crossover::alternatingPositionCrossover(const Chromosome &lhs, const Chromosome &rhs) {
    uint genesSize = lhs.genes.size();
    std::vector<bool> firstGenesInPath(genesSize, false), secondGenesInPath(genesSize, false);
    std::vector<uint> firstOffspringGenes(genesSize), secondOffspringGenes(genesSize);
    std::array<uint, 2> firstOffspringIndices{0, 0}, secondOffspringIndices{0, 0};
    for(uint i = 0; i < genesSize; i++) {
        insertGen(firstOffspringGenes[i], lhs, rhs, firstOffspringIndices[0],
                  firstOffspringIndices[1], firstGenesInPath);
        insertGen(secondOffspringGenes[i], rhs, lhs, secondOffspringIndices[1],
                  secondOffspringIndices[0], secondGenesInPath);
    }
    Chromosome firstOffspring{firstOffspringGenes, lhs.graph};
    Chromosome secondOffspring{secondOffspringGenes, rhs.graph};
    return std::min(firstOffspring, secondOffspring);
}

void Crossover::insertGen(uint &targetGen, const Chromosome &priorChr, const Chromosome &sideChr,
                          uint &priorChrIndex, uint &sideChrIndex, std::vector<bool> &genesInPath) {
    const Chromosome *firstChr, *secondChr;
    uint *firstChrIndex, *secondChrIndex;
    if(priorChrIndex <= sideChrIndex) {
        firstChr = &priorChr;
        secondChr = &sideChr;
        firstChrIndex = &priorChrIndex;
        secondChrIndex = &sideChrIndex;
    } else {
        firstChr = &sideChr;
        secondChr = &priorChr;
        firstChrIndex = &sideChrIndex;
        secondChrIndex = &priorChrIndex;
    }
    bool inserted{false};
    uint i{0};
    const Chromosome *currentChr;
    uint *currentChrIndex;
    while(!inserted) {
        if(i % 2 == 0) {
            currentChr = firstChr;
            currentChrIndex = firstChrIndex;
        } else {
            currentChr = secondChr;
            currentChrIndex = secondChrIndex;
        }
        uint candidGen = currentChr->genes[*currentChrIndex];
        if(!genesInPath[candidGen]) {
            targetGen = candidGen;
            inserted = true;
            genesInPath[candidGen] = true;
        }
        (*currentChrIndex)++;
        i++;
    }
}