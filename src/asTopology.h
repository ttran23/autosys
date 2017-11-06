//
//  asTopology.h
//  autosys
//
//  Created by Jason Tran on 11/5/17.
//

#ifndef asTopology_h
#define asTopology_h

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include <sstream>
#include <cctype>
#include <iterator>

using namespace std;

void parseTop(string file);
void writeFile(int tC, int cC, int eC, int total);
vector<string> split(const string &s, char delim);
#endif /* asTopology_h */
