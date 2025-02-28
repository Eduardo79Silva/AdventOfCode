#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int wordMatchCount(const std::vector<std::vector<char>> &crosswords,
                   const std::string &xPos) {
  // Parse the starting coordinates from xPos, which is in "y$x" format.
  int y = std::stoi(xPos.substr(0, xPos.find('$')));
  int x = std::stoi(xPos.substr(xPos.find('$') + 1));

  // The target word to match.
  const std::string word = "XMAS";
  int count = 0;

  // Define eight directions: (dy, dx)
  const std::vector<std::pair<int, int>> directions = {
      {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

  // Loop through each direction.
  for (const auto &[dy, dx] : directions) {
    bool match = true;
    // Check each letter of the word.
    for (size_t i = 0; i < word.size(); i++) {
      int ny = y + static_cast<int>(i) * dy;
      int nx = x + static_cast<int>(i) * dx;

      // Check if the new coordinates are within bounds and the letter matches.
      if (ny < 0 || ny >= static_cast<int>(crosswords.size()) || nx < 0 ||
          nx >= static_cast<int>(crosswords[ny].size()) ||
          crosswords[ny][nx] != word[i]) {
        match = false;
        break;
      }
    }
    if (match) {
      count++;
    }
  }

  return count;
}

int main() {
  std::ifstream fin("test.txt");
  std::vector<std::vector<char>> crosswords;
  std::vector<std::string> xCharIndexes;

  if (fin.is_open()) {
    std::string lineStr;
    int line = 0;
    while (std::getline(fin, lineStr)) {
      std::vector<char> row;
      std::cout << lineStr << std::endl;
      // Use an index-based loop so we know each character's position.
      for (size_t i = 0; i < lineStr.size(); i++) {
        char ch = std::toupper(lineStr[i]);
        row.push_back(ch);
        // If this character is an 'X', record its position.
        if (ch == 'X') {
          // Use the current index i (instead of lineStr.find(ch)) for the
          // column.
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

