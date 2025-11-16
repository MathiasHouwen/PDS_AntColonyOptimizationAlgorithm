#ifndef PDS_ANTCOLONYOPTIMIZATIONALGORITHM_ACO_H
#define PDS_ANTCOLONYOPTIMIZATIONALGORITHM_ACO_H

#include <vector>
#include <random>
#include "Graph.h"
#include "Ant.h"

class ACO {
private:
    const Graph& graph;
    int numAnts;
    double alpha;           // Influence of pheromone (tau)
    double beta;            // Influence of heuristic (eta = 1/distance)
    double evaporationRate; // Pheromone evaporation factor
    double Q;               // Constant controlling pheromone deposit amount
    std::vector<std::vector<double>> pheromone;
    std::vector<Ant> ants;
    std::mt19937 rng;

    int selectNextCity(int currentCity, const Ant& ant);
public:
    ACO(const Graph& graph,
        int numAnts,
        double alpha,
        double beta,
        double evaporationRate,
        double Q);

    void constructSolutions();
    void updatePheromones();

    std::pair<std::vector<int>, double> run(int iterations);
};


#endif