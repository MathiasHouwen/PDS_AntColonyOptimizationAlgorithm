#include "ACO_Serial.h"
#include <limits>

ACO_Serial::ACO_Serial(const Graph& graph, int numAnts, double alpha, double beta,
                       double evaporationRate, double Q)
    : ACO(graph, numAnts, alpha, beta, evaporationRate, Q) {}

void ACO_Serial::constructSolutions() {
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
        ant.visitCity(start);
    }
}

void ACO_Serial::updatePheromones() {
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

std::pair<std::vector<int>, double> ACO_Serial::run(int iterations) {
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
