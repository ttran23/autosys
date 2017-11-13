//
//  asInference.h
//  autosys_project
//
//  Created by Jason Tran on 11/12/17.
//

#ifndef asInference_h
#define asInference_h

#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>

std::multimap<int, int> sortDegree(std::multimap<int, int> degreeMap);
std::vector<int> traverse(std::multimap<int, int> map, std::multimap<int, int>* p2p, std::multimap<int, int>* p2c);
void writeClique(std::vector<int> clique);
#endif /* asInference_h */
