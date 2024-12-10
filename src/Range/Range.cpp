#include "Range.h"
#include "../Random/Random.h"

void Range::cutPart(uint rangeSize, uint &startCutOff, uint &endCutOff) {
    uint lastIndex = rangeSize - 1;
    startCutOff = Random::iRange(0u, lastIndex);
    endCutOff = Random::iRange(std::min(startCutOff + 1, lastIndex), lastIndex);
}