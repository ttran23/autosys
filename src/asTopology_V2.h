#ifndef ASTOPOLOGY_V2_H
#define ASTOPOLOGY_V2_H

#include "asNode.h"
#include <fstream>
#include <sstream>
#include <string>

std::vector<Node> parseFile2();
void calculateData(std::vector<int> node);
bool checkNode(int nodeCurrent, std::vector<Node> nodeList);
int findNode(int nodeCurrent, std::vector<Node> nodeList);
#endif // ASTOPOLOGY_V2_H
