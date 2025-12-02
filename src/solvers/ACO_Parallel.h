#pragma once
#include "ACO.h"
#include <vector>
#include <random>
#include <utility>

class ACO_Parallel : public ACO {
public:
    ACO_Parallel(const Graph& graph, int numAnts, double alpha, double beta,
                 double evaporationRate, double Q, unsigned seed = 123);

    std::pair<std::vector<int>, double> run(int iterations) override;

private:
    std::mt19937 rng;

    void constructSolutions() override;
    void updatePheromones() override;
};
