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

void traverse(std::multimap<int, int> map, std::multimap<int, int>* p2p, std::multimap<int, int>* p2c) {
    int currAS = 0;
    std::vector<int> clique;
    for (auto it = map.end(); it != map.begin(); it = map.lower_bound(it->first)) {
        if (currAS == 0) {
            currAS = it->second;
            clique.push_back(currAS);
            continue;
        }
        for (auto iter1 = p2p->begin(); iter1 != p2p->end(); iter1 = p2p->upper_bound(iter1->first)) {
            /*
            if ((iter1->first == it->second) || (iter1->second == it->second)) {
                break;
            }
             */
        }
    }
}
