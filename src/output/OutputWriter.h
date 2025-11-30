#include <string>
#include <vector>
#include "Result.h"

class OutputWriter {
private:
  std::string outputFileNameSerial;
  std::string outputFileNameParallel;
  std::vector<Result> bufferSerial; // tijdelijk opslaan van resultaten
  std::vector<Result> bufferParallel; // tijdelijk opslaan van resultaten

public:
  OutputWriter(std::string  fileNameSerial, std::string  fileNameParallel);

  // Voeg resultaat toe aan buffer (kan parallel threads veilig doen)
  void addResultSerial(const Result& result);
  void addResultParallel(const Result& result);

  // Schrijf alles in één keer naar bestand
  void writeAll();

  static void writeToFile(const std::vector<Result>& results, const std::string& fileName);
};
