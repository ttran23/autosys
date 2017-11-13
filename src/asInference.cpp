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

void traverse(std::multimap<int, int> map, std::multimap<int, int>* p2p, std::multimap<int, int>* p2c, std::vector<int>* clique) {
    int currAS = 0;
    bool doesNotExist = false;
    for (auto it = map.end(); it != map.begin(); it = map.lower_bound(it->first)) {
        if (currAS == 0) {
            currAS = it->second;
            clique->push_back(currAS);
            continue;
        }
        
        for (auto iter1 = p2p->begin(); iter1 != p2p->end(); iter1 = p2p->upper_bound(iter1->first)) {
            if (iter1->first == it->second) {
                currAS = iter1->first;
                clique->push_back(currAS);
                doesNotExist = false;
            }
            else if (iter1->second == it->second) {
                currAS = iter1->second;
                clique->push_back(currAS);
                doesNotExist = false;
            }
            else {
                doesNotExist = true;
            }
        }
        
        for (auto iter2 = p2c->begin(); iter2 != p2c->end(); iter2 = p2c->upper_bound(iter2->first)) {
            if (iter2->first == it->second) {
                currAS = iter2->first;
                clique->push_back(currAS);
                doesNotExist = false;
            }
            else if (iter2->second == it->second) {
                currAS = iter2->second;
                clique->push_back(currAS);
                doesNotExist = false;
            }
            else {
                doesNotExist = true;
            }
        }
        
        if (doesNotExist) {
            break;
        }
    }
}

void writeClique(std::vector<int>* clique) {
    
    // Open file
    std::ofstream outFile;
    // outFile.open("output_text_files/partThree.txt");
    outFile.open("/Users/Jason/Desktop/Xcode/ECE_478/autosys/src/dataset_text_files/partThree.txt");
    
    // Check that file exists
    if (!outFile) {
        std::cout << "Unable to open file\n";
        exit(1);
    }
    
    outFile << "Total size count of clique: " << clique->size() << std::endl;
    outFile << "First 10 nodes:" << std::endl;
    for (int i = 0; i < 10; i++) {
        outFile << clique->at(i) << std::endl;
    }
    
    outFile.close();
}
