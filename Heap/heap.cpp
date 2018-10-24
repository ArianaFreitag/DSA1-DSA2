#include "heap.h"

heap::heap(int capacity) {
  // create hash table
  mapping = new hashTable(capacity*2);
  data.resize(capacity+1);
  this->capacity = capacity;
  index = 0;
}

int heap::insert(const std::string &id, int key, void * pv) {
  if (index < capacity) {
    if (!(mapping->contains(id))) {
      index += 1;
      // insert the new item into the heap and hashtable
      data[index].id = id;
      data[index].key = key;
      data[index].pData = pv;
      mapping->insert(id, &data[index]);
      percolateUp(index);
    } else {
      return 2;
    }
  } else {
    return 1;
  }
  return 0;
}

int heap::setKey(const std::string &id, int key){
  if (mapping->contains(id)) {
    // create a reference to the specified node
    node * pNode = static_cast<node*> (mapping->getPointer(id));

    // keep the old key value and update it with the new
    int old = pNode->key;
    pNode->key = key;

    // call getPos to get the location of the node in the heap
    int loc = getPos(pNode);
    if (key < old) {
      percolateUp(loc);
    } else if (key > old){
      percolateDown(loc);
    }
    return 0;
  } else {
    return 1;
  }
}

int heap::deleteMin(std::string *pId, int *pKey, void *ppData) {
  // check to make sure the heap isn't empty
  if (index != 0) {
    // update values if specified
    if (pId != nullptr) {
      *pId = data[1].id;
    }
    if (pKey != nullptr) {
      *pKey = data[1].key;
    }
    if(ppData != nullptr) {
      *(static_cast<void**> (ppData)) = data[1].pData;
    }

    // remove the node from the hashtable and heap
    mapping->remove(data[1].id);
    data[1] = data[index];
    index -= 1;
    percolateDown(1);

    return 0;
  } else {
    return 1;
  }
}

int heap::remove(const std::string &id, int *pKey, void *ppData) {
  // check if the heap contains the id
  if (mapping->contains(id)) {
    node * pNode = static_cast<node*> (mapping->getPointer(id));
    if (pKey != nullptr) {
      *pKey = pNode->key;
    }
    if (ppData != nullptr) {
      *(static_cast<void**> (ppData)) = pNode->pData;
    }
    // remove the node from the hashtable and heap
    mapping->remove(id);
    int old = pNode->key;
    *pNode = data[index];
    int newk = pNode->key;
    index -= 1;
    // sort the heap to make sure all nodes in right spot
    int loc = getPos(pNode);
    if (newk < old) {
      percolateUp(loc);
    } else if (old < newk){
      percolateDown(loc);
    }
    return 0;
  } else {
    return 1;
  }
}

void heap::percolateUp(int posCur) {
  // temp node of data we want to move
  node temp = data[posCur];
  // do the swap and move through heap
  while (posCur > 1 && temp.key < data[posCur/2].key) {
    data[posCur] = data[posCur/2];
    mapping->setPointer(data[posCur].id, &data[posCur]);
    posCur /= 2;
  }
  // change the nodes position
  data[posCur] = temp;
  mapping->setPointer(data[posCur].id, &data[posCur]);
}

void heap::percolateDown(int posCur) {
  node temp = data[posCur];
  int target;
  int left, right;
  // do the swap and move through heap
  while (2*posCur <= index) {
    int left = 2*posCur;
    int right = left + 1;
    if (left < index && data[right].key < data[left].key) {
      target = right;
    } else {
      target = left;
    }
    if (data[target].key < temp.key) {
      data[posCur] = data[target];
      mapping->setPointer(data[posCur].id, &data[posCur]);
    } else {
      break;
    }
    posCur = target;
  }
  // change the nodes position
  data[posCur] = temp;
  mapping->setPointer(data[posCur].id, &data[posCur]);
}

int heap::getPos(node *pNode) {
  int pos = pNode - &data[0];
  return pos;
}
