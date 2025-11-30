#include "inputReader.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

InputReader::InputReader(std::string path)
    : inputFile(std::move(path)){}

Graph InputReader::loadGraphFromFile() {
    std::ifstream f(inputFile);
    if (!f.is_open()) {
        throw std::runtime_error("Kon graph file niet openen: " + inputFile);
    }

    int n;
    f >> n;
    Graph graph(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double d;
            f >> d;
            graph.setDistance(i, j, d);
        }
    }

    return graph;
}
