#include "Graph.h"

Graph::Graph(int n) : n(n), distance(n, std::vector<double>(n)) {}

void Graph::setDistance(int i, int j, double d) {
    distance[i][j] = d;
    distance[j][i] = d;
}

double Graph::getDistance(int i, int j) const {
    return distance[i][j];
}

int Graph::size() const {
    return n;
}