#include "OutputWriter.h"
#include <fstream>
#include <iostream>
#include <utility>

OutputWriter::OutputWriter(std::string  fileNameSerial, std::string  fileNameParallel)
    : outputFileNameSerial(std::move(fileNameSerial)), outputFileNameParallel(std::move(fileNameParallel))
{ }

void OutputWriter::addResultSerial(const Result& result) {
    bufferSerial.push_back(result);
}

void OutputWriter::addResultParallel(const Result& result) {
    bufferParallel.push_back(result);
}

void OutputWriter::writeToFile(const std::vector<Result> &results, const std::string &fileName) {
    std::ofstream ofs(fileName, std::ios::out); // overschrijft bestaand bestand
    if (!ofs) {
        std::cerr << "Fout bij openen bestand: " << fileName << std::endl;
        return;
    }

    ofs << "graphSize,numAnts,alpha,beta,evaporationRate,Q,duration(s)\n";

    for (const auto& r : results) {
        ofs << r.getGraphSize() << ","
            << r.getNumAnts() << ","
            << r.getAlpha() << ","
            << r.getBeta() << ","
            << r.getEvaporationRate() << ","
            << r.getQ() << ","
            << r.getDuration() << "\n";
    }
    ofs.close();
}


void OutputWriter::writeAll() {
    writeToFile(bufferSerial, outputFileNameSerial);
    writeToFile(bufferParallel, outputFileNameParallel);
}
