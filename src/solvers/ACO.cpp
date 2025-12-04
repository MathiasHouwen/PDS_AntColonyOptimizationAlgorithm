#include "ACO.h"
#include <cmath>
#include <iostream>

ACO::ACO(const Graph& graph, int numAnts, double alpha, double beta,
         double evaporationRate, double Q)
    : graph(graph),
      numAnts(numAnts),
      alpha(alpha), beta(beta),
      evaporationRate(evaporationRate), Q(Q),
      pheromone(graph.size(), std::vector<double>(graph.size(), 1.0)),
      rng(std::random_device{}())
{
    for (int i = 0; i < numAnts; ++i)
        ants.emplace_back(graph);
}

int ACO::selectNextCity(int currentCity, const Ant& ant) {
    std::vector<double> probabilities(graph.size());
    double sum = 0;

    for (int j = 0; j < graph.size(); j++) {
        if (!ant.isVisited(j)) {
            double tau = std::pow(pheromone[currentCity][j], alpha);
            double eta = std::pow(1.0 / graph.getDistance(currentCity, j), beta);
            probabilities[j] = tau * eta;
            sum += probabilities[j];
        }
    }

    std::uniform_real_distribution<> dist(0, sum);
    double r = dist(rng);

    double cumulative = 0;
    for (int j = 0; j < graph.size(); j++) {
        if (!ant.isVisited(j)) {
            cumulative += probabilities[j];
            if (r <= cumulative)
                return j;
        }
    }

    // fallback
    for (int j = 0; j < graph.size(); j++)
        if (!ant.isVisited(j)) return j;
    std::cout << " Fallback failed!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
    return -1;
}