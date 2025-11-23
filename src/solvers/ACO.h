#ifndef PDS_ANTCOLONYOPTIMIZATIONALGORITHM_ACO_H
#define PDS_ANTCOLONYOPTIMIZATIONALGORITHM_ACO_H

#include <vector>
#include <random>
#include "../Graph.h"
#include "../Ant.h"

// Abstract base class
class ACO {
protected:
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
    // Constructor
    ACO(const Graph& graph,
        int numAnts,
        double alpha,
        double beta,
        double evaporationRate,
        double Q);

    virtual void constructSolutions() = 0;
    virtual void updatePheromones() = 0;
    virtual std::pair<std::vector<int>, double> run(int iterations) = 0;

    virtual ~ACO() = default;

    int getNumAnts() { return numAnts; }
    double getAlpha() { return alpha; }
    double getBeta() { return beta; }
    double getEvaporationRate() { return evaporationRate; }
    double getQ() { return Q; }
};

#endif