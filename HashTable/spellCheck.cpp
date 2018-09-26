#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <ctime>
#include "hash.h"
using namespace std;

int main() {
  string inFile, outFile, dictionaryFile, line, word;
  bool ignore;
  char c;
  int i, wordCount;
  unsigned long lineNo = 0;
  clock_t start, end;
  ifstream input;
  ifstream dict;
  ofstream output;

  std::cout << "Enter the name of dictionary file: ";
  std::cin >> dictionaryFile;

  hashTable *dictionary = new hashTable(500000);

  start = clock();

  dict.open(dictionaryFile);
  if (!dict) {
    std::cout << "input failed to open"  << "\n";
  } else {
    while (!dict.eof()) {
      std::getline(dict, line);
      for (int i = 0; i < line.length(); i++) {
        line[i] = std::tolower(line[i]);
        wordCount = i;
      }
      dictionary->insert(line);
    }
  }
  dict.close();

  std::cout << wordCount << endl;
  end = clock();
  std::cout << "Total time (in seconds) to load dictionary into hash table: " << ((double)(end - start)) / CLOCKS_PER_SEC << endl;

  std::cout << "Enter the name of input file: ";
  std::cin >> inFile;

  std::cout << "Enter the name of output file: ";
  std::cin >> outFile;

  start = clock();

  input.open(inFile);
  if (!input) {
    std::cout << "input failed to open"  << "\n";
  }
  output.open(outFile);
  if (!output){
    std::cout << "output failed to open"  << "\n";
  }

  while (getline(input, line)) {
    lineNo++;
    for (i = 0; i <= line.length(); i++) {
      c = tolower(line[i]);
      int asciic = c;
      if (isalnum(c) || (asciic == 39) || (asciic == 45)) {
          word += c;
          if (isdigit(c)){
            ignore = true;
          }
      } else if ((ignore == false) && (word.length() > 0)) {
        if (word.length() > 20) {
          output << "Long word at line " << lineNo << ", starts: " << word.substr(0, 20) << endl;
        } else if (dictionary->contains(word) != true){
          output << "Unknown word at line " << lineNo << ": " << word << endl;
        }
        word = "";
      } else {
        word = "";
        ignore = false;
      }
    }
  }

  input.close();
  output.close();
  end = clock();

  std::cout << "Total time (in seconds) spent in spellcheck: " << ((double)(end - start)) / CLOCKS_PER_SEC << endl;

  return 0;
}
