#ifndef PDS_ANTCOLONYOPTIMIZATIONALGORITHM_ANT_H
#define PDS_ANTCOLONYOPTIMIZATIONALGORITHM_ANT_H

#include <vector>
#include "Graph.h"

class Ant {
private:
    const Graph& graph;
    std::vector<int> tour;
    std::vector<bool> visited;
    double tourLength;

public:
    Ant(const Graph& g);

    void visitCity(int city);
    bool isVisited(int city) const;

    void reset();

    const std::vector<int>& getTour() const;
    double getTourLength() const;
};

#endif