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
    std::ofstream ofs(fileName, std::ios::app); // overschrijft bestaand bestand
    if (!ofs) {
        std::cerr << "Fout bij openen bestand: " << fileName << std::endl;
        return;
    }

    for (const auto& r : results) {
        ofs << r.getGraphSize() << ","
            << r.getNumAnts() << ","
            << r.getAlpha() << ","
            << r.getBeta() << ","
            << r.getEvaporationRate() << ","
            << r.getQ() << ","
            << r.solution_length() << ","
            << r.error1() << ","
            << r.goal1() << ","
            << r.getDuration() << "\n";
    }
    ofs.close();
}


void OutputWriter::writeAll() {
    writeToFile(bufferSerial, outputFileNameSerial);
    writeToFile(bufferParallel, outputFileNameParallel);

    // --- Python script automatisch uitvoeren ---
    // int result = system("python ../src/output/plot.py");

    // if (result != 0) {
    //     std::cerr << "Fout bij uitvoeren van plot.py" << std::endl;
    // }
}

