#pragma once
#include <string>
#include "../../src/Graph.h"

class InputReader {
private:
    std::string inputFile;

public:
    explicit InputReader(std::string path);
    Graph loadGraphFromFile();
};
