#ifndef ASTOPOLOGY_H
#define ASTOPOLOGY_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>

void parsePartTwo(std::multimap<int, int>* p2p, std::multimap<int, int>* p2c);
void parseIPPrefix(std::multimap<double, std::string>* ip);
void processPartTwo(std::multimap<int, int>* p2p, std::multimap<int, int>* p2c);
void writePartTwo(int *bin, int tC, int cC, int eC);
std::vector<std::string> split(const std::string &s, char delim);
#endif // ASTOPOLOGY_H
