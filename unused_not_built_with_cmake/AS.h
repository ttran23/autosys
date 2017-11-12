//
//  AS.h
//  autosys
//
//  Created by Jason Tran on 11/5/17.
//

#ifndef AS_h
#define AS_h

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <cstring>
#include <string>
#include <cctype>

using namespace std;

class AS {
private:
    string name;
public:
    AS(string name);
    AS();
    string getName() { return name; }
    vector<AS *> peers;
    vector<AS *> customers;
};
#endif /* AS_h */
