#ifndef ASTOPOLOGY_V2_H
#define ASTOPOLOGY_V2_H

#include "asNode.h"
#include <fstream>
#include <sstream>
#include <string>
#include <map>

void parsePartTwo(std::multimap<int, int>* p2p, std::multimap<int, int>* p2c);
void parseIPPrefix(std::multimap<int, std::string>* ip);
std::map<int, Node *> processPartTwo(std::vector< std::vector<int> > nodeUnsorted);
bool checkSourceField(std::vector<Node> nodeList, int id);
bool checkTargetField(std::vector<Node> nodeList, int id);
int findNodeIndex(std::vector<Node> nodeList, int id);
Node checkExist(std::vector<Node> source, int id);
#endif // ASTOPOLOGY_V2_H
