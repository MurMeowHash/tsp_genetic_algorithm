#pragma once

#include "../Chromosome/Chromosome.h"

class Mutation {
public:
    static Chromosome insertionMutation(const Chromosome &chr);
//    static Chromosome inversionMutation(const Chromosome &chr);
    static Chromosome exchangeMutation(const Chromosome &chr);
};