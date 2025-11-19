#include <iostream>
#include "src/solvers/ACO.h"
#include "src/solvers/ACO_Serial.h"
#include "src/Graph.h"
#include "src/timer.h"

// double d[5][5] = {
//     {0, 2, 9, 10, 7},
//     {2, 0, 6, 4, 3},
//     {9, 6, 0, 8, 5},
//     {10, 4, 8, 0, 1},
//     {7, 3, 5, 1, 0}
// };
// TODO: MESCHIEN  EEN VISUALISTATIE?
int main() {
    // Zorgen dat we meerden graaf grootes proberen
    for (int n : {5, 10, 20, 40, 80}) {
        Graph graph(n);
        std::mt19937 rng(123);
        std::uniform_real_distribution<> dist(1.0, 10.0);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                graph.setDistance(i, j, (i==j ? 0 : dist(rng)));
            }
        }

        // TODO: ONDERZOEK NAAR INVLOED VAN PARAMETERS OP TIJD
        ACO_Serial aco(graph, 20, 1.0, 5.0, 0.5, 100.0);

        AutoAverageTimer timer("ACO Run Time");
        // TODO: INVLOED VAN ITERATION TESTEN OP DE TIJD
        for (int i = 0; i < 5; i++) {            // TODO: MAGIC NUMBER TRAILS
            timer.start();
            auto[resultTour, resultLength] = aco.run(100);
            timer.stop();

            // Code om de oplossing te zien
            // std::cout << "Best Tour: ";
            // for (int city : resultTour)
            //     std::cout << city << " ";
            // std::cout << "\nLength: " << resultLength << "\n";
        }

        timer.report();
    }
    return 0;
}

// EERSTE TIJDEN OP LAPTOP
// #ACO Run Time 0.0340074 +/- 0.00300681 sec (5 measurements)
// #ACO Run Time 0.0953628 +/- 0.00517369 sec (5 measurements)
// #ACO Run Time 0.317644 +/- 0.00709086 sec (5 measurements)
// #ACO Run Time 1.25334 +/- 0.071986 sec (5 measurements)
// #ACO Run Time 4.65721 +/- 0.100869 sec (5 measurements)