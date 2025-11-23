#pragma once
#include "ACO.h"

class ACO_Parallel : public ACO {
public:
    ACO_Parallel(const Graph& graph, int numAnts, double alpha, double beta,
                 double evaporationRate, double Q);

    void constructSolutions() override;
    void updatePheromones() override;

    std::pair<std::vector<int>, double> run(int iterations) override;
};
