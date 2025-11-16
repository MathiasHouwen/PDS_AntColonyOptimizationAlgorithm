#ifndef PDS_ANTCOLONYOPTIMIZATIONALGORITHM_GRAPH_H
#define PDS_ANTCOLONYOPTIMIZATIONALGORITHM_GRAPH_H

#include <vector>

class Graph {
private:
    int n;
    std::vector<std::vector<double>> distance;

public:
    Graph(int n);

    void setDistance(int i, int j, double d);
    double getDistance(int i, int j) const;

    int size() const;
};

#endif