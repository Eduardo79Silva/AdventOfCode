#include <algorithm>
#include <fstream>
#include <iostream>
#include <ostream>
#include <unordered_map>
#include <vector>

int main() {
  std::ifstream fin("input.txt");

  if (fin.is_open()) {

    int id1, id2;

    std::vector<int> ids1, ids2;

    while (fin >> id1) {
      fin >> id2;
      ids1.push_back(id1);
      ids2.push_back(id2);
    }

    std::sort(ids1.begin(), ids1.end());
    std::sort(ids2.begin(), ids2.end());

    int similarityScore = 0;

    int currentNumber = -1;
    int duplicateCount =
        0; 

    std::unordered_map<int, int> similarityMap;

    for (int i = 0; i < ids1.size(); i++) {
      if (ids1[i] == currentNumber) {
        duplicateCount++;
        continue;
      } else {

        if (currentNumber != -1) {
          similarityMap[currentNumber] += currentNumber * duplicateCount;
        }

        currentNumber = ids1[i];
        duplicateCount = 0;
      }

      for (int j = 0; j < ids2.size(); j++) {
        if (currentNumber == ids2[j]) {
          duplicateCount++;
        }
      }
    }

    for (auto i = similarityMap.begin(); i != similarityMap.end(); i++) {
      similarityScore += i->second;
    }

    std::cout << similarityScore << std::endl;

    fin.close();

  } else {
    std::cout << "Error opening file!" << std::endl;
  }

  return 0;
}
