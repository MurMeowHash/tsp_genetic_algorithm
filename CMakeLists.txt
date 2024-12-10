cmake_minimum_required(VERSION 3.29)
project(tsp_genetic_algorithm)

set(CMAKE_CXX_STANDARD 20)

add_executable(tsp_genetic_algorithm src/main.cpp
        src/Graph/Graph.cpp
        src/Graph/Graph.h
        src/utils/utils.h
        src/utils/utils.cpp
        src/Random/Random.h
        src/Random/Random.cpp
        src/GeneticAlgorithm/GeneticAlgorithm.cpp
        src/GeneticAlgorithm/GeneticAlgorithm.h
        src/GeneticAlgorithm/Chromosome/Chromosome.h
        src/GeneticAlgorithm/Crossover/Crossover.cpp
        src/GeneticAlgorithm/Crossover/Crossover.h
        src/GeneticAlgorithm/Mutation/Mutation.cpp
        src/GeneticAlgorithm/Mutation/Mutation.h
        src/GeneticAlgorithm/Chromosome/Chromosome.cpp
        src/Range/Range.cpp
        src/Range/Range.h
        src/GeneticAlgorithm/Optimization/Optimization.cpp
        src/GeneticAlgorithm/Optimization/Optimization.h
)
