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
  int i;
  unsigned long lineNo = 0;
  int wordCount = 0;
  clock_t start, end;
  ifstream input;
  ifstream dict;
  ofstream output;

  std::cout << "Enter the name of dictionary file: ";
  std::cin >> dictionaryFile;

  // create hashtable
  hashTable *dictionary = new hashTable(500000);

  start = clock();

  // load dictionary with words
  dict.open(dictionaryFile);
  if (!dict) {
    std::cout << "input failed to open"  << "\n";
  } else {
    // loop through each line of dictionary till eof
    while (!dict.eof()) {
      wordCount++;
      std::getline(dict, line);
      // make each char lowercase
      for (int i = 0; i < line.length(); i++) {
        line[i] = std::tolower(line[i]);
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

  // get each line of input file and loop through each one
  while (getline(input, line)) {
    lineNo++;
    // make each char lowercase
    for (i = 0; i <= line.length(); i++) {
      c = tolower(line[i]);
      int asciic = c;
      // check to see what char is and then add to word if its valid
      if (isalnum(c) || (asciic == 39) || (asciic == 45)) {
          word += c;
          if (isdigit(c)){
            ignore = true;
          }
      } else if ((ignore == false) && (word.length() > 0)) {
        // check for long
        if (word.length() > 20) {
          output << "Long word at line " << lineNo << ", starts: " << word.substr(0, 20) << endl;
          // hash table look up
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
