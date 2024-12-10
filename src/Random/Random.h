#pragma once

#include <random>
#include "../utils/utils.h"

class Random {
private:
    static std::random_device rd;
    static std::mt19937 mt;
public:
    template<class T>
    NODISCARD static T iRange(T lowerLimit, T upperLimit) {
        std::uniform_int_distribution<T> dist{lowerLimit, upperLimit};
        return dist(mt);
    }
    NODISCARD static double genProbability();
    NODISCARD static std::mt19937& getGenerator();
};