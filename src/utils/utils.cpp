#include "utils.h"
#include <cmath>

uint getNumbersCount(uint number) {
    uint numbersCount{0};
    while(number != 0) {
        number /= 10;
        numbersCount++;
    }
    return numbersCount;
}

uint getFirstNumber(uint number, uint numbersCount) {
    return number / static_cast<uint>(std::pow(10u, numbersCount - 1));
}