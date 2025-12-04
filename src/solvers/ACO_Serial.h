#ifndef PDS_ANTCOLONYOPTIMIZATIONALGORITHM_ACO_SERIAL_H
#define PDS_ANTCOLONYOPTIMIZATIONALGORITHM_ACO_SERIAL_H

#include "ACO.h"

// Serial implementation of ACO
class ACO_Serial : public ACO {
public:
    ACO_Serial(const Graph& graph, int numAnts, double alpha, double beta,
               double evaporationRate, double Q, unsigned seed);

    void constructSolutions() override;
    void updatePheromones() override;
    std::pair<std::vector<int>, double> run(int iterations) override;

    ~ACO_Serial() override = default;
};

#endif