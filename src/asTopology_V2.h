#ifndef ASTOPOLOGY_V2_H
#define ASTOPOLOGY_V2_H

#include "asNode.h"
#include <fstream>
#include <sstream>
#include <string>

std::vector< std::vector<int> > parsePartTwo();
std::vector<Node> processPartTwo(std::vector< std::vector<int> > nodeUnsorted);
bool checkSourceField(std::vector<Node> nodeList, int id);
bool checkTargetField(std::vector<Node> nodeList, int id);
int findNodeIndex(std::vector<Node> nodeList, int id);
Node checkExist(std::vector<Node> source, int id);
#endif // ASTOPOLOGY_V2_H
