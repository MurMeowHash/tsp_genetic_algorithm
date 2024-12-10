#pragma once

#include "../Chromosome/Chromosome.h"
#include <set>

class Optimization {
private:
    static void twoOptSwap(std::vector<uint> &genes, uint i, uint j);
    static uint calcRouteCost(const std::vector<uint> &genes, const Graph &costSrc, uint i, uint j);
    static uint calcTwoOptRouteCost(const std::vector<uint> &genes, const Graph &costSrc, uint i, uint j);
    static std::set<Chromosome> openNeighbors(Chromosome &chr);
public:
    static Chromosome twoOpt(const Chromosome &chr);
    static Chromosome hillClimbing(const Chromosome &chr);
};