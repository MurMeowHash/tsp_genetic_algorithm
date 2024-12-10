#include "Random.h"

std::random_device Random::rd;
std::mt19937 Random::mt(rd());

double Random::genProbability() {
    std::uniform_real_distribution<double> dist{0.0, 1.0};
    return dist(mt);
}

std::mt19937 &Random::getGenerator() {
    return mt;
}