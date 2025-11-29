#include <iostream>
#include <random>
#include "src/Graph.h"
#include "src/solvers/ACO_Serial.h"
#include "src/solvers/ACO_Parallel.h"
#include "src/timer.h"
#include "src/output/OutputWriter.h"

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

    // Stel de scheduler environment variable in
    std::string omp_sched = scheduler + ",1"; // chunk size = 1
#ifdef _WIN32
    _putenv_s("OMP_SCHEDULE", omp_sched.c_str());
#else
    setenv("OMP_SCHEDULE", omp_sched.c_str(), 1);
#endif

    // Output writer
    OutputWriter writer("src/output/resultsSerial.csv", "src/output/resultsParallel.csv");

    for (int n : {5, 10, 20, 40, 80}) {
        Graph graph(n);
        std::mt19937 rng(123); // vaste seed
        std::uniform_real_distribution<> dist(1.0, 10.0);

        // Vul graf met random afstanden
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                graph.setDistance(i, j, (i == j ? 0.0 : dist(rng)));

        // Parameters
        int numAnts = 20;
        double alpha = 1.0, beta = 5.0, evaporationRate = 0.5, Q = 100.0;
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
        double duration_serial = timer_serial.durationNanoSeconds() / 1e9;
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
        double duration_parallel = timer_parallel.durationNanoSeconds() / 1e9;
        writer.addResultParallel(Result(aco_parallel, duration_parallel, n));

        std::cout << "-----------------------------\n";
    }

    writer.writeAll();
    return 0;
}

//TODO: online test cases zoeken

//TODO: env variabelen
// hoeveelheid threads
