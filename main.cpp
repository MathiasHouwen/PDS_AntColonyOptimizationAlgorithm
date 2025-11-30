#include <iostream>
#include <random>
#include <sstream>
#include "src/Graph.h"
#include "src/solvers/ACO_Serial.h"
#include "src/solvers/ACO_Parallel.h"
#include "src/timer.h"
#include "src/output/OutputWriter.h"

// Helper: vector<int> -> "a -> b -> c" string
std::string tourToString(const std::vector<int>& tour) {
    std::ostringstream oss;
    for (size_t i = 0; i < tour.size(); i++) {
        oss << tour[i];
        if (i + 1 < tour.size()) oss << " -> ";
    }
    return oss.str();
}

int main(int argc, char* argv[]) {

    if (argc < 2) {
        std::cout << "Gebruik: " << argv[0] << " <scheduler>\n";
        std::cout << "Opties: static, dynamic, guided\n";
        return 1;
    }

    std::string scheduler = argv[1];
    if (scheduler != "static" && scheduler != "dynamic" && scheduler != "guided") {
        std::cout << scheduler << " is geen geldige optie\n";
        return 1;
    }

    // OpenMP scheduler instellen
    std::string omp_sched = scheduler + ",1";
#ifdef _WIN32
    _putenv_s("OMP_SCHEDULE", omp_sched.c_str());
#else
    setenv("OMP_SCHEDULE", omp_sched.c_str(), 1);
#endif

    OutputWriter writer("src/output/resultsSerial.csv", "src/output/resultsParallel.csv");

    for (int n : {5, 10, 20, 40, 80}) {

        Graph graph(n);
        std::mt19937 rng(123);
        std::uniform_real_distribution<> dist(1.0, 10.0);

        // Random graf opvullen
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                graph.setDistance(i, j, (i == j ? 0.0 : dist(rng)));

        // ACO parameters
        int numAnts = 20;
        double alpha = 1.0, beta = 5.0, evaporationRate = 0.5, Q = 100.0;
        int iterations = 100;

        // --- Seriële ACO ---
        ACO_Serial aco_serial(graph, numAnts, alpha, beta, evaporationRate, Q);
        AutoAverageTimer timer_serial("ACO_Serial Run Time");

        std::vector<int> bestTourSerial;
        double bestLengthSerial = 1e18;

        for (int t = 0; t < 5; t++) {
            timer_serial.start();
            auto[resultTour, resultLength] = aco_serial.run(iterations);
            timer_serial.stop();

            // update beste resultaat
            if (resultLength < bestLengthSerial) {
                bestTourSerial = resultTour;
                bestLengthSerial = resultLength;
            }
        }

        timer_serial.report(std::cout);
        writer.addResultSerial(Result(aco_serial, timer_serial.durationNanoSeconds() / 1e9, n));

        std::cout << "\nBeste seriële route voor n=" << n << ":\n";
        std::cout << "  " << tourToString(bestTourSerial)
                  << " (lengte: " << bestLengthSerial << ")\n\n";

        // --- Parallel ACO ---
        ACO_Parallel aco_parallel(graph, numAnts, alpha, beta, evaporationRate, Q);
        AutoAverageTimer timer_parallel("ACO_Parallel Run Time" + std::to_string(n));

        std::vector<int> bestTourParallel;
        double bestLengthParallel = 1e18;

        for (int t = 0; t < 5; t++) {
            timer_parallel.start();
            auto[resultTour, resultLength] = aco_parallel.run(iterations);
            timer_parallel.stop();

            if (resultLength < bestLengthParallel) {
                bestTourParallel = resultTour;
                bestLengthParallel = resultLength;
            }
        }

        timer_parallel.report(std::cout);
        writer.addResultParallel(Result(aco_parallel, timer_parallel.durationNanoSeconds() / 1e9, n));

        std::cout << "Beste parallelle route voor n=" << n << ":\n";
        std::cout << "  " << tourToString(bestTourParallel)
                  << " (lengte: " << bestLengthParallel << ")\n";
        std::cout << "-----------------------------\n\n";
    }

    writer.writeAll();
    return 0;
}

//TODO: online test cases zoeken

//TODO: env variabelen
// hoeveelheid threads
