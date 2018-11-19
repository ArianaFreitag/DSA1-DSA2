#include <iostream>
#include <sstream>
#include <iterator>
#include "graph.h"

graph::graph() {
  graphHashTable = new hashTable(500000);
  capacity = 0;
}

bool graph::dijkstra(const std::string &start) {
  node *begin = (node *) graphHashTable->getPointer(start);
  begin->dist = 0;
  begin->path.push_back(start);
  heap graphHeap(capacity);
  graphHeap.insert(start, begin->dist, begin);
  for (std::list<node *>::const_iterator it = nodeList.begin(), end = nodeList.end(); it != end; ++it) {
    if ((*it)->name != start) {
      graphHeap.insert((*it)->name, (*it)->dist, *it);
    }
  }

  node *nodeTemp;
  for (int i = 0; i < capacity; i++) {
    graphHeap.deleteMin(nullptr, nullptr, &nodeTemp);
    for (std::list<edge>::const_iterator it = nodeTemp->adj.begin(), end = nodeTemp->adj.end(); it != end && nodeTemp->dist != INT_MAX; ++it) {
      if (!it->dest->known && it->dest->dist > (it->cost + nodeTemp->dist)) {
        it->dest->path.clear();
        it->dest->path.insert(it->dest->path.begin(), nodeTemp->path.begin(), nodeTemp->path.end());
        it->dest->path.push_back(it->dest->name);
        it->dest->dist = (it->cost + nodeTemp->dist);
        graphHeap.setKey(it->dest->name, (it->cost + nodeTemp->dist));
      }
    }
    nodeTemp->known = true;
  }
  return true;
}

bool graph::nodeExists(const std::string &node) {
  return (graphHashTable->contains(node));
}

void graph::insert(const std::string &line) {
  node *nodeTemp1, *nodeTemp2;
  edge edgeTemp;
  std::vector<std::string> tokens;
  std::string token;
  std::istringstream iss(line);
  while(std::getline(iss, token, ' ')) { // tokenize line to get each param
    tokens.push_back(token);
  }

  if (!graphHashTable->contains(tokens[0])) {
    nodeTemp1 = new node;
    nodeTemp1->name = tokens[0];
    nodeTemp1->known = false;
    nodeTemp1->dist = INT_MAX;
    nodeList.push_back(nodeTemp1);
    graphHashTable->insert(tokens[0], nodeTemp1);
    capacity++;
  } else {
    nodeTemp1 = (node *) graphHashTable->getPointer(tokens[0]);
  }

  if (!graphHashTable->contains(tokens[1])) {
    nodeTemp2 = new node;
    nodeTemp2->name = tokens[1];
    nodeTemp2->known = false;
    nodeTemp2->dist = INT_MAX;
    nodeList.push_back(nodeTemp2);
    graphHashTable->insert(tokens[1], nodeTemp2);
    capacity++;
  } else {
    nodeTemp2 = (node *) graphHashTable->getPointer(tokens[1]);
  }

  edgeTemp.cost = stoi(tokens[2]);
  edgeTemp.dest = nodeTemp2;
  nodeTemp1->adj.push_back(edgeTemp);
}

void graph::returnGraph(std::ofstream &out) {
  for (std::list<node*>::const_iterator it = nodeList.begin(), end = nodeList.end(); it != end; ++it) {
    out << (*it)->name << ": ";
    if ((*it)->dist == INT_MAX) {
      out << "NO PATH" << std::endl;
    } else {
      out << (*it)->dist << " [";
      for (std::list<std::string>::const_iterator it2 = (*it)->path.begin(), end2 = (*it)->path.end(); it2 != end2; ++it2) {
        out << *it2;
        if (std::next(it2, 1) != end2) out << ", ";
      }
      out << "]" << std::endl;
    }
  }
}
