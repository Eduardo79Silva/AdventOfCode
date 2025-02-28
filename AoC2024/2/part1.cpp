#include <cstddef>
#include <fstream>
#include <iostream>
#include <iterator>
#include <ostream>
#include <vector>

bool isReportSafe(std::vector<int> report, bool hasProblemDampener) {
  int isIncreasing = -1;
  bool isDangerousReport = false;


  for (int i = 1; i < report.size(); i++) {

    int levelDifference = report[i - 1] - report[i];

    if (isIncreasing == -1) {
      if (levelDifference < 0) {
        isIncreasing = 0;
      } else if (levelDifference > 0) {
        isIncreasing = 1;
      }
    }

    if ((levelDifference == 0 or abs(levelDifference) > 3) or
        (isIncreasing && levelDifference < 0) or
        (!isIncreasing && levelDifference > 0)) {
      if (!hasProblemDampener) {
        return false;
      }
      isDangerousReport = true;
      break;
    }
  }

  if (isDangerousReport) {
    std::vector<int> temp;

    for (int i = 0; i < report.size(); i++) {
      temp = report;
      temp.erase(temp.begin() + i);
      bool isSafe = isReportSafe(temp, false);
      if (isSafe) {
        return true;
      }
    }
    return false;
  }


  return true;
}

int main() {
  std::ifstream fin("input.txt");

  if (fin.is_open()) {

    int currentReportLevel = -1;

    int safeReportCount = 0;

    std::vector<int> report;
    while (fin >> currentReportLevel) {
      report.push_back(currentReportLevel);

      if (fin.peek() == '\n') {
        bool isSafe = isReportSafe(report, true);
        if (isSafe) {
          safeReportCount++;
        }
	report.clear();
        fin.get();
      }
    }

    std::cout << safeReportCount << std::endl;

    fin.close();
  } else {
    std::cout << "Error opening file!" << std::endl;
  }

  return 0;
}
