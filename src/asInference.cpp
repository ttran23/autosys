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
