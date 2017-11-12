#ifndef ASTOPOLOGY_V2_H
#define ASTOPOLOGY_V2_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>

void parsePartTwo(std::multimap<int, int>* p2p, std::multimap<int, int>* p2c);
void parseIPPrefix(std::multimap<int, int>* p2p, std::multimap<int, int>* p2c, std::multimap<int, int>* ip);
void processPartTwo(std::multimap<int, int>* p2p, std::multimap<int, int>* p2c);
#endif // ASTOPOLOGY_V2_H
