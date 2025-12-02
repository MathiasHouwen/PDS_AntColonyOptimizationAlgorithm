#include <iostream>
#include <random>
#include "src/Graph.h"
#include "src/solvers/ACO_Serial.h"
#include "src/solvers/ACO_Parallel.h"
#include "src/timer.h"
#include "src/output/OutputWriter.h"
#include "./src/input/inputReader.h"
#include <omp.h>

std::string tourToString(const std::vector<int>& tour) {
    std::ostringstream oss;
    for (size_t i = 0; i < tour.size(); i++) {
        oss << tour[i];
        if (i + 1 < tour.size()) oss << " -> ";
    }
    return oss.str();
}

int main(int argc, char* argv[]) {

    if (argc < 3) {
        std::cerr << "Gebruik: ./prog <scheduler> <threads>\n";
        return 1;
    }

    std::string scheduler = argv[1];
    if (scheduler != "static" && scheduler != "dynamic" && scheduler != "guided") {
        std::cerr << "Ongeldige scheduler: " << scheduler << "\n";
        return 1;
    }

    // --- Threads correct parsen
    int threads = std::stoi(argv[2]);

    // --- Scheduler instellen via OMP_SCHEDULE
    std::string omp_sched = scheduler + ",1";
#ifdef _WIN32
    _putenv_s("OMP_SCHEDULE", omp_sched.c_str());
#else
    setenv("OMP_SCHEDULE", omp_sched.c_str(), 1);
#endif

    OutputWriter writer("src/output/resultsSerial.csv", "src/output/resultsParallel.csv");
    InputReader reader("src/input/graph.txt");
    Graph graph = reader.loadGraphFromFile();
    int n = graph.size();

    int numAnts = threads;
    omp_set_num_threads(threads);

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
        if (resultLength < bestLengthSerial) {
            bestTourSerial = resultTour;
            bestLengthSerial = resultLength;
        }
    }

    writer.addResultSerial(Result(aco_serial, timer_serial.durationNanoSeconds() / 1e9, n));

    std::cout << "\nBeste seriële route:\n";
    std::cout << "  " << tourToString(bestTourSerial)
              << " (lengte: " << bestLengthSerial << ")\n\n";

    // --- Parallel ACO ---
    ACO_Parallel aco_parallel(graph, numAnts, alpha, beta, evaporationRate, Q);
    AutoAverageTimer timer_parallel("ACO_Parallel Run Time");

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

    writer.addResultParallel(Result(aco_parallel, timer_parallel.durationNanoSeconds() / 1e9, n));

    std::cout << "Beste parallelle route:\n";
    std::cout << "  " << tourToString(bestTourParallel)
              << " (lengte: " << bestLengthParallel << ")\n";

    writer.writeAll();
    return 0;
}

/*
 * die seed is moeilijk te realiseren aangezien elke ant dan dezelfde sequence aan random nummers zou moeten
 * krijgen, dit zou ook niet enorm veel variatie moeten geven waardoor ik dit gwn zou laten
 * voor wat het is.
 */