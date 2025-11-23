#include "OutputWriter.h"
#include <fstream>
#include <iostream>

OutputWriter::OutputWriter(const std::string& fileName)
    : outputFileName(fileName)
{ }

void OutputWriter::addResult(const Result& result) {
    buffer.push_back(result);
}

void OutputWriter::writeAll() {
    std::ofstream ofs(outputFileName, std::ios::out); // overschrijft bestaand bestand
    if (!ofs) {
        std::cerr << "Fout bij openen bestand: " << outputFileName << std::endl;
        return;
    }

    // Schrijf header
    ofs << "graphSize,numAnts,alpha,beta,evapRate,Q,duration(s)\n";

    for (const auto& r : buffer) {
        ofs << r.getGraphSize() << ","
            << r.getNumAnts() << ","
            << r.getAlpha() << ","
            << r.getBeta() << ","
            << r.getEvaporationRate() << ","
            << r.getQ() << ","
            << r.getDuration()
            << "\n";
    }

    ofs.close();
    std::cout << "Alle resultaten geschreven naar " << outputFileName << std::endl;
}
