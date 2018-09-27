#include "hash.h"

// set up with large prime numbers
int primes[] = { 98317, 196613, 393241, 786433, 1572869, 3145739, 6291469, 12582917, 25165843, 50331653, 100663319, 201326611, 402653189, 805306457, 1610612741 };
bool currentRehash;

hashTable::hashTable(int size) {
  unsigned int prime = getPrime(size);
  data.resize(prime);
  capacity = prime;
  filled = 0;
  //clear data vector before making hash table
  for (int i = 0; i < data.size(); i++){
    data[i].isOccupied = false;
    data[i].isDeleted = false;
  }
}

int hashTable::insert(const std::string &key, void *pv) {
  int delSpot = -1;
  int hashNum = hash(key);
  if (2*filled >= capacity) {
    if (rehash() == false) {
      return 2;
    }
  }
  while (data[hashNum].isOccupied == true) {
    if (data[hashNum].key == key) {
      if (data[hashNum].isDeleted == false) {
        return 1;
      } else {
        data[hashNum].isDeleted = false;
        return 0;
      }
    } else {
      if (data[hashNum].isDeleted == true && delSpot == -1) {
        delSpot = hashNum;
      }
      if (hashNum != (capacity - 1)) {
        hashNum++;
      } else {
        hashNum = 0;
      }
    }
  }
  //to check if data goes in deleted spot or new spot
  if (delSpot != -1) {
    hashNum = delSpot;
  }
  data[hashNum].key = key;
  data[hashNum].isOccupied = true;
  data[hashNum].isDeleted = false;
  data[hashNum].pv = pv;
  filled++;
  return 0;
}

bool hashTable::contains(const std::string &key) {
  if (findPos(key) == -1) {
    return false;
  } else {
    return true;
  }
}

int hashTable::hash(const std::string &key) {
  unsigned int seed = 131;
  unsigned int hash = 0;
  for(std::size_t i = 0; i < key.length(); i++)
  {
    hash = (hash * seed) + key[i];
  }
  return hash % capacity;
}

int hashTable::findPos(const std::string &key) {
  int hashNum = hash(key);
  while (data[hashNum].isOccupied) {
    if (data[hashNum].key == key) {
      if (!data[hashNum].isDeleted) {
        return hashNum;
      } else {
        return -1;
      }
    } else {
      if (hashNum != (capacity - 1)) {
        hashNum++;
      } else {
        hashNum = 0;
      }
    }
  }
  return -1;
}

bool hashTable::rehash() {
  int newPrime = getPrime(2*capacity);
  std::cout << "rehashing"  << "\n";
  //copy old vector to newData and resize old vector to be larger
  std::vector<hashItem> newData = data;
  try {
    data.resize(newPrime);
  }
  catch (std::bad_alloc) {
    return 2;
  }
  capacity = newPrime;
  filled = 0;
  for (int i = 0; i < newPrime; i++){
    data[i].isOccupied = false;
    data[i].isDeleted = false;
  }
  //insert data back to old (rehashed) vector
  for (int i = 0; i < newData.size(); i++) {
    if (newData[i].isOccupied == true && newData[i].isDeleted == false) {
        insert(newData[i].key, newData[i].pv);
    }
  }
  return 1;
}

unsigned int hashTable::getPrime(int size) {
  for (int i = 0; i < sizeof(primes)/sizeof(int); i++) {
    if (size <= primes[i]) {
      return primes[i];
    }
  }
}
