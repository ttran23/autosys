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
	int foundInSet = 0;
    std::vector<int> output;

	std::multimap<int, int> allConnections = *p2p;
	for (auto it = p2c->begin(); it != p2c->end(); it++) {
		allConnections.insert(std::make_pair(it->first, it->second));
	}
	std::multimap<int, int> allConnectionsFlipped = flip_map(allConnections);

    for (auto it = map.rbegin(); it != map.rend(); it++) {
        currAS = it->second;	// Current highest deg AS
        found = false;
        if (it == map.rbegin()) {	// First node, always pushed to set S
            output.push_back(currAS);
            continue;
        }
        
		foundInSet = 0;
		// Go through current list, to make sure all connections are valid.
		for (auto outIt = output.begin(); outIt != output.end(); outIt++) {
			// Set the current output, should be 6939, then next loop will be 6939, 174, etc
			int currInSet = *outIt;
			found = false;
			// Iterate through first column list for if any connection (p2p or p2c) is found. Probably will take ages to run
			for (auto iter1 = allConnections.begin(); iter1 != allConnections.end(); iter1 = allConnections.upper_bound(iter1->first)) {
				// Check if source is our current AS, and second is an element in the set.
				if (iter1->first == currAS) {
					for (unsigned int i = 0; i < allConnections.count(currAS); i++) {
						if ((iter1->first == currAS && iter1->second == currInSet)
							|| (iter1->second == currAS && iter1->first == currInSet)) {
							foundInSet++;
							found = true;
							break;
						}
						iter1++;
					}
				}
				if (found) break;
			}
			if (found) continue;

			// Iterate through second column
			for (auto iter1 = allConnectionsFlipped.begin(); iter1 != allConnectionsFlipped.end(); iter1 = allConnectionsFlipped.upper_bound(iter1->first)) {
				// Check if source is our current AS, and second is an element in the set.
				if (iter1->first == currAS) {
					for (unsigned int i = 0; i < allConnectionsFlipped.count(currAS); i++) {
						if ((iter1->first == currAS && iter1->second == currInSet)
							|| (iter1->second == currAS && iter1->first == currInSet)) {
							foundInSet++;
							found = true;
							break;
						}
						iter1++;
					}
				}
				if (found) break;
			}
		}

		// If the amount found in set == size, then all connections accounted for
		if (foundInSet >= output.size()) {
			output.push_back(currAS);	// Add to output vector
			doesNotExist = false;
			found = true;
			continue;	// No need to check p2c as curr AS already found all.
		}
		else {
			doesNotExist = true;
			found = false;
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
    outFile.open("output_text_files/partThree.txt");
    //outFile.open("/Users/Jason/Desktop/Xcode/ECE_478/autosys/src/output_text_files/partThree.txt");
    
    // Check that file exists
    if (!outFile) {
        std::cout << "Unable to open file\n";
        exit(1);
    }
    
    outFile << "Table 1/Graph 5:\nTotal size count of clique: " << clique.size() << std::endl;
    outFile << "First 10 nodes:";
    for (int i = 0; i < 10 && i < clique.size(); i++) {
		outFile << std::endl << clique.at(i);
    }
    
    outFile.close();
}
