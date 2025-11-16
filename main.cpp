#include <iostream>
#include "src/solvers/ACO.h"
#include "src/solvers/ACO_Serial.h"
#include "src/Graph.h"

int main() {
    int n = 5;
    Graph graph(n);

    double d[5][5] = {
        {0, 2, 9, 10, 7},
        {2, 0, 6, 4, 3},
        {9, 6, 0, 8, 5},
        {10, 4, 8, 0, 1},
        {7, 3, 5, 1, 0}
    };

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            graph.setDistance(i, j, d[i][j]);

    ACO_Serial aco(graph, 20, 1.0, 5.0, 0.5, 100.0);

    auto[resultTour, resultLength] = aco.run(100);

    std::cout << "Best Tour: ";
    for (int city : resultTour)
        std::cout << city << " ";
    std::cout << "\nLength: " << resultLength << "\n";

    return 0;
}
