#include <fstream>
#include <iostream>
#include <ostream>
#include <regex>
#include <string>
#include <vector>

std::vector<std::string> findEnabledZones(std::string line) {
  std::regex enabledZonePattern("do\\(\\)(.*?)don't\\(\\)");
  std::regex disabledZonePattern("don't\\(\\)(.*?)do\\(\\)");
  std::vector<std::string> matches;
  std::smatch match;

  std::regex_search(line, match, disabledZonePattern);

  matches.push_back(match.prefix());

  while (std::regex_search(line, match, enabledZonePattern)) {
    matches.push_back(match.str());
    line = match.suffix();
  }

  return matches;
}

std::vector<std::string> findMultiplication(std::string line) {
  // match the pattern "mul(\d*,\d*)"
  std::regex multiplicationPattern("mul\\((\\d*),(\\d*)\\)");

  std::vector<std::string> matches;
  std::smatch match;

  while (std::regex_search(line, match, multiplicationPattern)) {
    matches.push_back(match.str());
    line = match.suffix();
  }

  return matches;
}

int main() {
  std::ifstream fin("input.txt");

  if (fin.is_open()) {
    std::string file_data;
    std::string line;

    while (std::getline(fin, line)) {
      file_data.insert(file_data.end(), line.begin(), line.end());
    }

    std::vector<std::string> enabledZones = findEnabledZones(file_data);

    std::vector<std::string> matches;

    for (const auto &enabledZone : enabledZones) {
      std::vector<std::string> newMatches = findMultiplication(enabledZone);
      std::cout << newMatches[0] << std::endl;
      matches.insert(matches.end(), newMatches.begin(), newMatches.end());
    }

    std::cout << matches.size() << std::endl;

    int sum = 0;
    for (const auto &match : matches) {
      // take the numbers from  a string like "mul(312,54523)" and multiply them
      // std::cout << match << std::endl;
      int firstNumber = std::stoi(match.substr(4, match.find(',') - 4));
      int secondNumber =
          std::stoi(match.substr(match.find(',') + 1, match.size() - 1));
      sum += firstNumber * secondNumber;
    }

    std::cout << "Sum: " << sum << std::endl;

    fin.close();
  } else {
    std::cout << "Error opening file!" << std::endl;
  }

  return 0;
}
