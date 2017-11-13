//
//  asInference.cpp
//  autosys
//
//  Created by Jason Tran on 11/12/17.
//

#include <stdio.h>
#include "asInference.h"

template<typename A, typename B>
std::pair<B,A> flip_pair(const std::pair<A,B> &p) {
    return std::pair<B,A>(p.second, p.first);
}

template<typename A, typename B>
std::multimap<B,A> flip_map(const std::multimap<A,B> &src) {
    std::multimap<B,A> dst;
    std::transform(src.begin(), src.end(), std::inserter(dst, dst.begin()), flip_pair<A,B>);
    return dst;
}

std::multimap<int, int> sortDegree(std::multimap<int, int> degreeMap) {
    std::multimap<int, int> sorted = flip_map(degreeMap);
    return sorted;
}

std::vector<int> traverse(std::multimap<int, int> map, std::multimap<int, int>* p2p, std::multimap<int, int>* p2c) {
    int currAS = 0;
    bool doesNotExist = false;
    bool found = false;
    std::vector<int> output;
    for (auto it = map.rbegin(); it != map.rend(); it++) {
        currAS = it->second;
        found = false;
        if (it == map.rbegin()) {
            output.push_back(currAS);
            continue;
        }
        
        for (auto iter1 = p2p->begin(); iter1 != p2p->end(); iter1 = p2p->upper_bound(iter1->first)) {
            if (iter1->first == it->second) {
                //currAS = iter1->first;
                output.push_back(currAS);
                doesNotExist = false;
                found = true;
                break;
            }
            else if (iter1->second == it->second) {
                //currAS = iter1->second;
                output.push_back(currAS);
                doesNotExist = false;
                found = true;
                break;
            }
            else {
                doesNotExist = true;
            }
        }
        
        if (!found) {
            for (auto iter2 = p2c->begin(); iter2 != p2c->end(); iter2 = p2c->upper_bound(iter2->first)) {
                if (iter2->first == it->second) {
                    //currAS = iter2->first;
                    output.push_back(currAS);
                    doesNotExist = false;
                    break;
                }
                else if (iter2->second == it->second) {
                    //currAS = iter2->second;
                    output.push_back(currAS);
                    doesNotExist = false;
                    break;
                }
                else {
                    doesNotExist = true;
                }
            }
        }
        
        
        if (doesNotExist) {
            return output;
        }
    }
    
    return output;
}

void writeClique(std::vector<int> clique) {
    
    // Open file
    std::ofstream outFile;
    //outFile.open("output_text_files/partThree.txt");
    outFile.open("/Users/Jason/Desktop/Xcode/ECE_478/autosys/src/output_text_files/partThree.txt");
    
    // Check that file exists
    if (!outFile) {
        std::cout << "Unable to open file\n";
        exit(1);
    }
    
    outFile << "Total size count of clique: " << clique.size() << std::endl;
    outFile << "First 10 nodes:" << std::endl;
    for (int i = 0; i < 10 && i < clique.size(); i++) {
        outFile << clique.at(i) << std::endl;
    }
    
    outFile.close();
}
