//
//  asTopology.cpp
//  autosys
//
//  Created by Jason Tran on 11/5/17.
//

#include "asTopology.h"

bool parseTop(string file, vector<AS *> nodes) {
    
    // Open file
    ifstream inFile;
    inFile.open(file.c_str());
    // Check that file exists
    if (!inFile) {
        cout << "Unable to open file\n";
        exit(1);
    }
    bool result = false;
    vector<string> listLine;
    
    // Get each line
    string inLine;
    AS *firstNode;
    AS *secondNode;
    
    while (getline(inFile, inLine)) {
        string::size_type index;
        if ((index = inLine.find("#")) == string::npos) {
            listLine = split(inLine, '|');
            firstNode = check(listLine.at(0), nodes);
            secondNode = check(listLine.at(1), nodes);
            if (!existNode(*firstNode, nodes)) { nodes.push_back(firstNode); }
            if (!existNode(*secondNode, nodes)) { nodes.push_back(secondNode); }
            if ((index = listLine.at(2).find("0")) != string::npos) {
                firstNode->peers.push_back(secondNode);
                secondNode->peers.push_back(firstNode);
            }
            else if ((index = listLine.at(2).find("-1")) != string::npos) { firstNode->customers.push_back(secondNode); }
            else {
                cout << "Something went wrong when reading the line.";
                exit(1);
            }
        }
    }
    inFile.close();
    return result;
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

AS *check(string name, vector<AS *> asNodes) {
    bool found = false;
    AS *result;
    int i = 0;
    
    for (i = 0; i < asNodes.size(); i++) {
        if (asNodes.at(i)->getName().compare(name) == 0) {
            found = true;
            break;
        }
    }
    if (found) {
        result = asNodes.at(i);
    }
    else {
        result = new AS(name);
    }
    return result;
}

bool existNode(AS node, vector<AS *> asNodes) {
    bool result = false;
    
    for (int i = 0; i < asNodes.size(); i++) {
        if (asNodes.at(i)->getName().compare(node.getName()) == 0) {
            result = true;
            break;
        }
    }
    
    return result;
}
