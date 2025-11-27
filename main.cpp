#include <iostream>
#include <random>
#include "src/Graph.h"
#include "src/solvers/ACO_Serial.h"
#include "src/solvers/ACO_Parallel.h"
#include "src/timer.h"
#include "src/output/OutputWriter.h"

int main() {
    // Output writer
    OutputWriter writer("../src/output/resultsSerial.csv", "../src/output/resultsParallel.csv");

    // Probeer verschillende grafgroottes
    for (int n : {5, 10, 20, 40, 80}) {
        Graph graph(n);
        std::mt19937 rng(123);
        std::uniform_real_distribution<> dist(1.0, 10.0);

        // Vul graf met random afstanden
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                graph.setDistance(i, j, (i == j ? 0.0 : dist(rng)));
            }
        }

        // Parameters voor ACO
        int numAnts = 20;
        double alpha = 1.0;
        double beta = 5.0;
        double evaporationRate = 0.5;
        double Q = 100.0;
        int iterations = 100;

        // Seriële ACO
        ACO_Serial aco_serial(graph, numAnts, alpha, beta, evaporationRate, Q);
        AutoAverageTimer timer_serial("ACO_Serial Run Time");
        for (int t = 0; t < 5; t++) {
            timer_serial.start();
            auto[resultTour_serial, resultLength_serial] = aco_serial.run(iterations);
            timer_serial.stop();
        }
        timer_serial.report(std::cout);
        double duration_serial = timer_serial.durationNanoSeconds() / 1e9; // seconden
        writer.addResultSerial(Result(aco_serial, duration_serial, n));

        // Parallel ACO
        ACO_Parallel aco_parallel(graph, numAnts, alpha, beta, evaporationRate, Q);
        AutoAverageTimer timer_parallel("ACO_Parallel Run Time" + std::to_string(n));
        for (int t = 0; t < 5; t++) {
            timer_parallel.start();
            auto[resultTour_parallel, resultLength_parallel] = aco_parallel.run(iterations);
            timer_parallel.stop();
        }
        timer_parallel.report(std::cout);
        double duration_parallel = timer_parallel.durationNanoSeconds() / 1e9; // seconden
        writer.addResultParallel(Result(aco_parallel, duration_parallel, n));

        std::cout << "-----------------------------\n";
    }

    writer.writeAll();

    return 0;
}
