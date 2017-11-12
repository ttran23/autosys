#include "asTopology.h"

//Temporary, debug time
#include <chrono>
#include <ctime>

void parseIPPrefix(std::multimap<int, std::string>* ip) {
    std::ifstream inFile;
	inFile.open("dataset_text_files/routeviews-rv2-20171110-1200.pfx2as.txt");
    //inFile.open("/Users/Jason/Desktop/Xcode/ECE_478/autosys/src/dataset_text_files/routeviews-rv2-20171110-1200.pfx2as.txt");
    
    if (!inFile) {
        std::cout << "Unable to open file in parseIP\n";
        exit(1);
    }
    
    std::string inLine;
    std::string prefix, length, ASnum, prefixTemp;
    int AS;
    while (std::getline(inFile, inLine)) {
        std::stringstream iss;
        iss << inLine;
        iss >> prefix >> length >> AS;
        //AS = std::stoi(ASnum);
        prefixTemp.append(prefix + "/" + length);
        ip->insert(std::make_pair(AS, prefixTemp));
        prefixTemp.clear();
    }
    
    inFile.close();
}

void parsePartTwo(std::multimap<int, int>* p2p, std::multimap<int, int>* p2c) {

	// Open file
	std::ifstream inFile;
	inFile.open("dataset_text_files/20170901.as-rel2.txt");
    //inFile.open("/Users/Jason/Desktop/Xcode/ECE_478/autosys/src/dataset_text_files/20170901.as-rel2.txt");

	// Check that file exists
	if (!inFile) {
		std::cout << "Unable to open file in parsePartTwo\n";
		exit(1);
	}

	// Get each line
	std::string inLine;
	int x1, x2, t;
	char pipeThrow;
	while (std::getline(inFile, inLine)) {
		if (inLine.at(0) == '#')
			continue;
		std::stringstream iss;
		iss << inLine;
		iss >> x1 >> pipeThrow >> x2 >> pipeThrow >> t;
        if ( t == 0 ) { p2p->insert(std::make_pair(x1, x2)); }
        else if ( t == -1 ) { p2c->insert(std::make_pair(x1, x2)); }
        else {
            std::cout << "Something went wrong creating maps!" << std::endl;
            exit(-1);
        }
	}

	// Close file and return unsorted node list
	inFile.close();
}

void processPartTwo(std::multimap<int, int>* p2p, std::multimap<int, int>* p2c) {
	// Degree Map
	std::multimap<int, int> degreeMap;
	
	// Iterate through p2p and p2c
	for (auto it = p2p->begin(); it != p2p->end(); it = p2p->upper_bound(it->first)) {
		degreeMap.insert(std::make_pair(it->first, p2p->count(it->first) + p2c->count(it->first)));
	}

	for (auto it = p2c->begin(); it != p2c->end(); it = p2c->upper_bound(it->first)) {
		degreeMap.insert(std::make_pair(it->first, p2c->count(it->first)));
	}

	// Setting into bins
	int bin_trash = 0, bin_1 = 0, bin_2_5 = 0, bin_5_100 = 0, bin_100_200 = 0, bin_200_1000 = 0, bin_1000_inf = 0;

	for (auto it = degreeMap.begin(); it != degreeMap.end(); it++) {
		if (it->second > 1000) {	
			bin_1000_inf++;	
		}
		else if (it->second > 200) {
			bin_200_1000++;
		}
		else if (it->second > 100) {
			bin_100_200++;
		}
		else if (it->second > 5) {
			bin_5_100++;
		}
		else if (it->second > 1) {
			bin_2_5++;
		}
		else if (it->second == 1) {
			bin_1++;
		}
		else {
			bin_trash++;
		}
	}

	// TODO: Write to File Instead of Console
	std::cout << "Bin trash: " << bin_trash << std::endl;
	std::cout << "Bin 1: "	<< bin_1 << std::endl;
	std::cout << "Bin 2-5: " << bin_2_5 << std::endl;
	std::cout << "Bin 5-100: " << bin_5_100 << std::endl;
	std::cout << "Bin 100-200: " << bin_100_200 << std::endl;
	std::cout << "Bin 200-1000: " << bin_200_1000 << std::endl;
	std::cout << "Bin 1000+: " << bin_1000_inf << std::endl;
}
