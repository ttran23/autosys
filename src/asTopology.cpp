//
//  asTopology.cpp
//  autosys
//
//  Created by Jason Tran on 11/5/17.
//

#include "asTopology.h"

void parseTop(string file) {
    
    // Open file
    ifstream inFile;
    inFile.open(file.c_str());
    // Check that file exists
    if (!inFile) {
        cout << "Unable to open file\n";
        exit(1);
    }
    vector<string> listLine;
    vector<string> providerAs;
    vector<string> customerAs;
    string provide;
    string cust;
    string peer1;
    string peer2;
    string etc;
    int choice;
    
    // Get each line
    string inLine, asClass;
    while (getline(inFile, inLine)) {
        string::size_type index;
        if ((index = inLine.find("#")) == string::npos) {
            listLine = split(inLine, '|');
        }
    }
    inFile.close();
}

template<typename Output>
void split(const string &s, char delim, Output result) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        *(result++) = item;
    }
}

vector<string> split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, back_inserter(elems));
    return elems;
}
