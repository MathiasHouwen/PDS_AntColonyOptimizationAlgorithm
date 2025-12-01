#include "ACO_Parallel.h"
#include <omp.h>
#include <limits>
#include <iostream>

ACO_Parallel::ACO_Parallel(const Graph& graph, int numAnts, double alpha, double beta,
                           double evaporationRate, double Q, unsigned seed)
    : ACO(graph, numAnts, alpha, beta, evaporationRate, Q),
      rng(seed)
{

}

void ACO_Parallel::constructSolutions() {
    std::uniform_int_distribution<> dist(0, graph.size() - 1);

    #pragma omp parallel for schedule(runtime)
    for (auto & ant : ants) {
        ant.reset();
        int start = dist(rng);
        ant.visitCity(start);

        while (ant.getTour().size() < graph.size()) {
            int current = ant.getTour().back();
            int next = selectNextCity(current, ant);
            ant.visitCity(next);
        }
        std::cout << " uitgevoerd door thread "
              << omp_get_thread_num() << "\n";
    }
}

void ACO_Parallel::updatePheromones() {
    int n = graph.size();

    #pragma omp parallel for collapse(2) schedule(runtime)
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            pheromone[i][j] *= (1 - evaporationRate);

    std::vector localPhero(
        omp_get_max_threads(), std::vector(n * n, 0.0)
    );

    #pragma omp parallel for schedule(runtime)
    for (const auto & ant : ants) {
        int tid = omp_get_thread_num();
        const auto& tour = ant.getTour();
        double contrib = Q / ant.getTourLength();

        for (int i = 0; i < tour.size() - 1; i++) {
            int a = tour[i];
            int b = tour[i + 1];
            localPhero[tid][a * n + b] += contrib;
            localPhero[tid][b * n + a] += contrib;
        }
    }

    #pragma omp parallel for collapse(2) schedule(runtime)
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int t = 0; t < omp_get_max_threads(); t++)
                pheromone[i][j] += localPhero[t][i * n + j];
}

std::pair<std::vector<int>, double> ACO_Parallel::run(int iterations) {
    double bestLength = std::numeric_limits<double>::infinity();
    std::vector<int> bestTour;

    for (int it = 0; it < iterations; it++) {
        constructSolutions();
        updatePheromones();

        #pragma omp parallel for schedule(runtime)
        for (const auto & ant : ants) {
            double L = ant.getTourLength();
            #pragma omp critical
            {
                if (L < bestLength) {
                    bestLength = L;
                    bestTour = ant.getTour();
                }
            }
        }
    }

    return {bestTour, bestLength};
}
