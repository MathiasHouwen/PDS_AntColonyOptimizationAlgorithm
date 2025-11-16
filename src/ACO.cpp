#include "ACO.h"
#include <cmath>
#include <limits>

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
        cumulative += probabilities[j];
        if (r <= cumulative)
            return j;
    }

    // fallback
    for (int j = 0; j < graph.size(); j++)
        if (!ant.isVisited(j)) return j;

    return -1;
}

void ACO::constructSolutions() {
    std::uniform_int_distribution<> dist(0, graph.size() - 1);

    for (auto& ant : ants) {
        ant.reset();

        int start = dist(rng);
        ant.visitCity(start);

        while (ant.getTour().size() < graph.size()) {
            int current = ant.getTour().back();
            int next = selectNextCity(current, ant);
            ant.visitCity(next);
        }
    }
}

void ACO::updatePheromones() {
    for (auto& row : pheromone)
        for (double& p : row)
            p *= (1 - evaporationRate);

    for (const auto& ant : ants) {
        double contrib = Q / ant.getTourLength();
        const auto& tour = ant.getTour();

        for (int i = 0; i < tour.size() - 1; i++) {
            int a = tour[i];
            int b = tour[i + 1];

            pheromone[a][b] += contrib;
            pheromone[b][a] += contrib;
        }
    }
}

std::pair<std::vector<int>, double> ACO::run(int iterations) {
    double bestLength = std::numeric_limits<double>::infinity();
    std::vector<int> bestTour;

    for (int it = 0; it < iterations; it++) {
        constructSolutions();
        updatePheromones();

        for (const auto& ant : ants) {
            if (ant.getTourLength() < bestLength) {
                bestLength = ant.getTourLength();
                bestTour = ant.getTour();
            }
        }
    }

    return {bestTour, bestLength};
}
