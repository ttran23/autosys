#ifndef ASTOPOLOGY_H
#define ASTOPOLOGY_H

#include "asInference.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>

void parsePartTwo(std::multimap<int, int>* p2p, std::multimap<int, int>* p2c);
void parseIPPrefix(std::multimap<std::string, double>* ip);
void processPartTwo(std::multimap<int, int>* p2p, std::multimap<int, int>* p2c, std::multimap<std::string, double>* prefixMap);
void writePartTwo(int *bin, int tC, int cC, int eC, int *ipBin);
std::vector<std::string> split(const std::string &s, char delim);
void ipHistogram(std::multimap<std::string, int>* prefixMap, int *bin);
#endif // ASTOPOLOGY_H
