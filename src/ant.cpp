#include "ant.h"

Ant::Ant(const Graph &g)
    : graph(g), visited(g.size(), false), tourLength(0) {
}

void Ant::visitCity(int city) {
    if (!tour.empty()) {
        int last = tour.back();
        tourLength += graph.getDistance(last, city);
    }
    tour.push_back(city);
    visited[city] = true;
}

bool Ant::isVisited(int city) const {
    return visited[city];
}

void Ant::reset() {
    tour.clear();
    std::fill(visited.begin(), visited.end(), false);
    tourLength = 0;
}

const std::vector<int> &Ant::getTour() const {
    return tour;
}

double Ant::getTourLength() const {
    return tourLength;
}
