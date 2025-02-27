#include <algorithm>
#include <fstream>
#include <iostream>
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

    int totalDistance = 0;

    for (int i = 0; i < ids1.size(); i++) {
      totalDistance += abs(ids1[i] - ids2[i]);
    }

    std::cout << "Total distance: " << totalDistance << std::endl;

    fin.close();

  } else {
    std::cout << "Error opening file!" << std::endl;
  }

  return 0;
}
