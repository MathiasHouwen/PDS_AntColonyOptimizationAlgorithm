#pragma once
#include <string>
#include "../timer.h"
#include "../solvers/ACO.h"  // of ACO_Serial/ACO_Parallel

class Result {
private:
    int numAnts;
    double alpha;
    double beta;
    double evaporationRate;
    double Q;
    int graphSize;
    double duration; // runtime in seconden
    double solutionLength;
    int error;
    int goal;

public:
    // Constructor haalt alle parameters uit een ACO object
    Result(ACO& aco, double durationSeconds, int graphSize, double solutionLength, int error, int goal)
        : numAnts(aco.getNumAnts()), alpha(aco.getAlpha()), beta(aco.getBeta()),
          evaporationRate(aco.getEvaporationRate()), Q(aco.getQ()), graphSize(graphSize),
          duration(durationSeconds), solutionLength(solutionLength), error(error), goal(goal)
    {}

    // Getters
    int getNumAnts() const { return numAnts; }
    double getAlpha() const { return alpha; }
    double getBeta() const { return beta; }
    double getEvaporationRate() const { return evaporationRate; }
    double getQ() const { return Q; }
    int getGraphSize() const { return graphSize; }
    double getDuration() const { return duration; }

    double solution_length() const {
        return solutionLength;
    }

    int error1() const {
        return error;
    }

    int goal1() const {
        return goal;
    }
};
