#include "Graph.h"
#include "../Random/Random.h"

Graph::Graph(uint nodeCount, uint minDistance, uint maxDistance)
: adjacencyMatrix(nodeCount) {
    resizeAdjacencyRows(nodeCount);
    genCompleteGraph(minDistance, maxDistance);
}

void Graph::resizeAdjacencyRows(uint nodeCount) {
    for(auto &row : adjacencyMatrix) {
        row.resize(nodeCount);
    }
}

void Graph::genCompleteGraph(uint minDistance, uint maxDistance) {
    for(uint i = 0; i < adjacencyMatrix.size(); i++) {
        for(uint j = 0; j < adjacencyMatrix[i].size(); j++) {
            if(i != j) {
                adjacencyMatrix[i][j] = Random::iRange(minDistance, maxDistance);
            }
        }
    }
}

uint Graph::getSize() const {
    return adjacencyMatrix.size();
}
