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

  node *temp;
  for (int i = 0; i < capacity; i++) {
    graphHeap.deleteMin(nullptr, nullptr, &temp);
    for (std::list<edge>::const_iterator it = temp->adj.begin(), end = temp->adj.end(); it != end && temp->dist != INT_MAX; ++it) {
      if (!it->dest->known && it->dest->dist > (it->cost + temp->dist)) {
        it->dest->path.clear();
        it->dest->path.insert(it->dest->path.begin(), temp->path.begin(), temp->path.end());
        it->dest->path.push_back(it->dest->name);
        it->dest->dist = (it->cost + temp->dist);
        graphHeap.setKey(it->dest->name, (it->cost + temp->dist));
      }
    }
    temp->known = true;
  }
  return true;
}

bool graph::nodeExists(const std::string &node) {
  return (graphHashTable->contains(node));
}

void graph::insert(const std::string &line) {
  node *temp1, *temp2;
  edge tempe;
  std::vector<std::string> tokens;
  std::string token;
  std::istringstream iss(line);
  while(std::getline(iss, token, ' ')) {
    tokens.push_back(token);
  }

  if (!graphHashTable->contains(tokens[0])) {
    temp1 = new node;
    temp1->name = tokens[0];
    temp1->known = false;
    temp1->dist = INT_MAX;
    nodeList.push_back(temp1);
    graphHashTable->insert(tokens[0], temp1);
    capacity++;
  } else {
    temp1 = (node *) graphHashTable->getPointer(tokens[0]);
  }

  if (!graphHashTable->contains(tokens[1])) {
    temp2 = new node;
    temp2->name = tokens[1];
    temp2->known = false;
    temp2->dist = INT_MAX;
    nodeList.push_back(temp2);
    graphHashTable->insert(tokens[1], temp2);
    capacity++;
  } else {
    temp2 = (node *) graphHashTable->getPointer(tokens[1]);
  }

  tempe.cost = stoi(tokens[2]);
  tempe.dest = temp2;
  temp1->adj.push_back(tempe);
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
