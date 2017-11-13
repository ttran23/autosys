//
//  asInference.h
//  autosys_project
//
//  Created by Jason Tran on 11/12/17.
//

#ifndef asInference_h
#define asInference_h

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>

std::multimap<int, int> sortDegree(std::multimap<int, int> degreeMap);
void traverse(std::multimap<int, int> map, std::multimap<int, int>* p2p, std::multimap<int, int>* p2c );
#endif /* asInference_h */
