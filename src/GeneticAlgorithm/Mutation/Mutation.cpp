#include "Mutation.h"
#include "../../Random/Random.h"
#include <functional>
#include "../../Range/Range.h"

Chromosome Mutation::insertionMutation(const Chromosome &chr) {
    int lastIndex = static_cast<int>(chr.genes.size() - 1);
    int randGenIndex = Random::iRange(0, lastIndex);
    int randInsertionIndex = Random::iRange(0, lastIndex);
    if(randGenIndex == randInsertionIndex) {
        return chr;
    }
    std::function<bool(int&)> advanceFunction;
    if(randGenIndex < randInsertionIndex) {
        advanceFunction = [randInsertionIndex](int &index){ return ++index < randInsertionIndex; };
    } else {
        randGenIndex--;
        advanceFunction = [randInsertionIndex](int &index){ return --index >= randInsertionIndex; };
    }
    std::vector<uint> offspringGenes(chr.genes);
    bool notReachedEnd{true};
    while(notReachedEnd) {
        std::swap(offspringGenes[randGenIndex], offspringGenes[randGenIndex + 1]);
        notReachedEnd = advanceFunction(randGenIndex);
    }
    return Chromosome{offspringGenes, chr.graph};
}

//Chromosome Mutation::inversionMutation(const Chromosome &chr) {
//    uint startCutOff, endCutOff;
//    Range::cutPart(chr.genes.size(), startCutOff, endCutOff);
//    uint
//}

Chromosome Mutation::exchangeMutation(const Chromosome &chr) {
    uint lastIndex = chr.genes.size() - 1;
    std::vector<uint> mutatedGenes(chr.genes);
    uint firstGenIndex = Random::iRange(0u, lastIndex);
    uint secondGenIndex = Random::iRange(0u, lastIndex);
    std::swap(mutatedGenes[firstGenIndex], mutatedGenes[secondGenIndex]);
    return Chromosome{mutatedGenes, chr.graph};
}