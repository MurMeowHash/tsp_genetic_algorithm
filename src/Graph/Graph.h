#pragma once

#include <vector>
#include "../utils/utils.h"

class Chromosome;
class Optimization;

class Graph {
    friend class Chromosome;
    friend class Optimization;
private:
    std::vector<std::vector<uint>> adjacencyMatrix;
    void resizeAdjacencyRows(uint nodeCount);
    void genCompleteGraph(uint minDistance, uint maxDistance);
public:
    Graph(uint nodeCount, uint minDistance, uint maxDistance);
    NODISCARD uint getSize() const;
};