#include <fstream>
#include <iostream>
#include <string>
#include "graph.h"

int main() {
  std::string start;
  std::string inFile, outPath;
  std::string line;
  graph gph;

  std::cout << "\nEnter name of graph file: ";
  std::cin >> inFile;
  std::ifstream graphList (inFile.c_str());
  if (graphList.is_open()) {
    while (std::getline(graphList, line)) {
      gph.insert(line);
    }
    graphList.close();
  }

  while (!gph.nodeExists(start)) {
    std::cout << "Enter a valid vertix ID for the starting vertex: ";
    std::cin >> start;
  }

  clock_t begin = clock();
  gph.dijkstra(start);
  clock_t end = clock();
  double elapsed_secs = ((double)(end-begin)) / CLOCKS_PER_SEC;
  std::cout << "Total time (in seconds) to apply dijkstra's algorithm: " << elapsed_secs << "\n";
  std::cout << "Enter name of output file: ";
  std::cin >> outPath;
  std::ofstream outFile (outPath.c_str());
  gph.returnGraph(outFile);
  outFile.close();
  return 0;
}
