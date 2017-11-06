//
//  asTopology.cpp
//  autosys
//
//  Created by Jason Tran on 11/5/17.
//

#include "asTopology.h"

vector<AS> parseTop(string file) {
    
    // Open file
    ifstream inFile;
    inFile.open(file.c_str());
    // Check that file exists
    if (!inFile) {
        cout << "Unable to open file\n";
        exit(1);
    }
    vector<string> listLine;
    vector<AS> output;
    
    // Get each line
    string inLine;
    AS *firstNode = NULL;
    AS *secondNode = NULL;
    while (getline(inFile, inLine)) {
        string::size_type index;
        if ((index = inLine.find("#")) == string::npos) {
            listLine = split(inLine, '|');
            firstNode = new AS(listLine.at(0));
            secondNode = new AS(listLine.at(1));
            check(*firstNode, *secondNode, output);
            if ((index = listLine.at(2).find("0")) != string::npos) {
                firstNode->peers.push_back(*secondNode);
                secondNode->peers.push_back(*firstNode);
            }
            else if ((index = listLine.at(2).find("-1")) != string::npos) { firstNode->customers.push_back(*secondNode); }
            else {
                cout << "Something went wrong when reading the line.";
                exit(1);
            }
        }
    }
    inFile.close();
    return output;
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

void check(AS first, AS second, vector<AS> &asNodes) {
    bool foundFirst = false;
    bool foundSecond = false;
    
    for (int i = 0; i < asNodes.size(); i++) {
        if (asNodes.at(i).getName().compare(first.getName()) == 0) { foundFirst = true; }
        if (asNodes.at(i).getName().compare(second.getName()) == 0) { foundSecond = true; }
    }
    if (!foundFirst) { asNodes.push_back(first); }
    if (!foundSecond) { asNodes.push_back(second); }
}
