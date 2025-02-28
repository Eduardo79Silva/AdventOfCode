#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int wordMatchCount(const std::vector<std::vector<char>> &crosswords,
                   const std::string &xPos) {
  int y = std::stoi(xPos.substr(0, xPos.find('$')));
  int x = std::stoi(xPos.substr(xPos.find('$') + 1));

  const std::vector<std::pair<int, int>> directions = {{-1, -1}, {-1, 1}};

  bool match = true;
  if (y == 0 or y == (int)crosswords.size() - 1 or x == 0 or
      x == (int)crosswords[y].size() - 1) {
    return 0;
  }

  for (const auto &[dy, dx] : directions) {
    const int ny = y + dy;
    const int nx = x + dx;
    const int oy = y - dy;
    const int ox = x - dx;

    if (crosswords[ny][nx] == crosswords[oy][ox] or
        (crosswords[ny][nx] != 'M' && crosswords[ny][nx] != 'S') or
        (crosswords[oy][ox] != 'M' && crosswords[oy][ox] != 'S')) {
      std::cout << crosswords[ny][nx] << crosswords[oy][ox] << std::endl;
      match = false;
    }
  }
  if (match)
    return 1;

  return 0;
}

int main() {
  std::ifstream fin("input.txt");
  std::vector<std::vector<char>> crosswords;
  std::vector<std::string> xCharIndexes;

  if (fin.is_open()) {
    std::string lineStr;
    int line = 0;
    while (std::getline(fin, lineStr)) {
      std::vector<char> row;
      std::cout << lineStr << std::endl;
      for (size_t i = 0; i < lineStr.size(); i++) {
        char ch = std::toupper(lineStr[i]);
        row.push_back(ch);
        if (ch == 'A') {
          xCharIndexes.push_back(std::to_string(line) + '$' +
                                 std::to_string(i));
        }
      }
      crosswords.push_back(row);
      line++;
    }
    fin.close();

    int totalCount = 0;
    for (const auto &xCharIndex : xCharIndexes) {
      int matchCount = wordMatchCount(crosswords, xCharIndex);
      totalCount += matchCount;
    }

    std::cout << "Total count: " << totalCount << std::endl;

  } else {
    std::cout << "Error opening file!" << std::endl;
  }

  return 0;
}
