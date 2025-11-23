#pragma once
#include <string>
#include <vector>
#include "Result.h"

class OutputWriter {
private:
  std::string outputFileName;
  std::vector<Result> buffer; // tijdelijk opslaan van resultaten

public:
  OutputWriter(const std::string& fileName);

  // Voeg resultaat toe aan buffer (kan parallel threads veilig doen)
  void addResult(const Result& result);

  // Schrijf alles in één keer naar bestand
  void writeAll();
};
