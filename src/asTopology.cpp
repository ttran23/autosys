#include "asTopology.h"

//Temporary, debug time
#include <chrono>
#include <ctime>

void parseIPPrefix(std::multimap<std::string, double>* ip) {
    std::ifstream inFile;
	// inFile.open("dataset_text_files/routeviews-rv2-20171110-1200.pfx2as.txt");
    inFile.open("/Users/Jason/Desktop/Xcode/ECE_478/autosys/src/dataset_text_files/routeviews-rv2-20171110-1200.pfx2as.txt");
    
    if (!inFile) {
        std::cout << "Unable to open file in parseIP\n";
        exit(1);
    }
    
    std::string inLine;
    std::string prefix, length, ASnum, prefixTemp;
    std::vector<std::string> nodeList;
    double AS;
    while (std::getline(inFile, inLine)) {
        std::stringstream iss;
        iss << inLine;
        iss >> prefix >> length >> ASnum;
        prefixTemp.append(prefix + "/" + length);
        std::string::size_type index;
        if ((index = ASnum.find('_')) != std::string::npos) {
            nodeList = split(ASnum, '_');
            for (int i = 0; i < nodeList.size(); i++) {
                ip->insert(std::make_pair(prefixTemp, std::stod(nodeList.at(i))));
            }
        }
        else {
            AS = std::stod(ASnum);
            ip->insert(std::make_pair(prefixTemp, AS));
        }
        prefixTemp.clear();
    }
    
    inFile.close();
}

template<typename Output>
void split(const std::string &s, char delim, Output result) {
    std::stringstream ss(s);
    std::string item;
    while (getline(ss, item, delim)) {
        *(result++) = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, back_inserter(elems));
    return elems;
}


void parsePartTwo(std::multimap<int, int>* p2p, std::multimap<int, int>* p2c) {

	// Open file
	std::ifstream inFile;
	// inFile.open("dataset_text_files/20170901.as-rel2.txt");
    inFile.open("/Users/Jason/Desktop/Xcode/ECE_478/autosys/src/dataset_text_files/20170901.as-rel2.txt");

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

void ipHistogram(std::multimap<std::string, int>* prefixMap, int *bin) {
    int classTemp = 0;
    int AScount = 0;
    std::string prefixTemp;
    std::string::size_type index;
    for (auto it = prefixMap->begin(); it != prefixMap->end(); it = prefixMap->upper_bound(it->first)) {
        prefixTemp.append(it->first);
        index = prefixTemp.find('.');
        prefixTemp.erase(prefixTemp.begin() + index, prefixTemp.end());
        classTemp = std::stoi(prefixTemp);
        AScount = prefixMap->count(it->first);
        if (classTemp >= 1 && classTemp <= 127) {
            bin[0] += AScount;
        }
        else if (classTemp >= 128 && classTemp <= 191) {
            bin[1] += AScount;
        }
        else if (classTemp >= 192 && classTemp <= 223) {
            bin[2] += AScount;
        }
        else if (classTemp >= 224 && classTemp <= 239) {
            bin[3] += AScount;
        }
        else if (classTemp >= 240 && classTemp <= 255) {
            bin[4] += AScount;
        }
        else {
            std::cout << "Something went wrong when creating the IP histogram!" << std::endl;
            exit(-1);
        }
        prefixTemp.clear();
    }
}

void processPartTwo(std::multimap<int, int>* p2p, std::multimap<int, int>* p2c, std::multimap<std::string, double>* prefixMap) {
	// Degree Map, AS Classifications
	std::multimap<int, int> degreeMap;
	int eCount = 0, cCount = 0, tCount = 0;
    std::multimap<std::string, int>* prefixDegreeMap = new std::multimap<std::string, int>();
    int ipBin[5] = { 0, 0, 0, 0, 0 };
    std::vector<int> uniqueNodes;
    std::multimap<int, int> sorted;
	// Iterate through p2p and p2c
	for (auto it = p2p->begin(); it != p2p->end(); it = p2p->upper_bound(it->first)) {
        if (std::find(uniqueNodes.begin(), uniqueNodes.end(), it->first) == uniqueNodes.end()) {
            uniqueNodes.push_back(it->first);
        }
        if (std::find(uniqueNodes.begin(), uniqueNodes.end(), it->second) == uniqueNodes.end()) {
            uniqueNodes.push_back(it->second);
        }
		degreeMap.insert(std::make_pair(it->first, p2p->count(it->first) + p2c->count(it->first)));
		if (p2p->count(it->first) >= 1 && p2c->count(it->first) == 0) {
			cCount++;	// At least one peer and no customer
		}
	}

	for (auto it = p2c->begin(); it != p2c->end(); it = p2c->upper_bound(it->first)) {
        if (std::find(uniqueNodes.begin(), uniqueNodes.end(), it->first) == uniqueNodes.end()) {
            uniqueNodes.push_back(it->first);
        }
        if (std::find(uniqueNodes.begin(), uniqueNodes.end(), it->second) == uniqueNodes.end()) {
            uniqueNodes.push_back(it->second);
        }
		degreeMap.insert(std::make_pair(it->first, p2c->count(it->first)));
		tCount++; // At least one customer, increment transit
		if (p2p->count(it->second) + p2c->count(it->second) <= 2
			&& p2p->count(it->second) == 0
			&& p2c->count(it->second) == 0) {
			eCount++;	// Deg <= 2 with no peer and no customer
			// Only cycling through here because no need to traverse the p2p link
			// since any p2p link is disqualified.
		}
	}
    
    // PART 3 related function
    sorted = sortDegree(degreeMap);
    

    for (auto it = prefixMap->begin(); it != prefixMap->end(); it = prefixMap->upper_bound(it->first)) {
        if (it->second <= 2147483647) {
            int temp = it->second;
            if (std::find(uniqueNodes.begin(), uniqueNodes.end(), temp) != uniqueNodes.end()) {
                prefixDegreeMap->insert(std::make_pair(it->first, temp));
            }
        }
    }
    
    ipHistogram(prefixDegreeMap, ipBin);
    
	// Setting into bins for Graph 2
	int bin[7] = { 0, 0, 0, 0, 0, 0, 0 };
	
	for (auto it = degreeMap.begin(); it != degreeMap.end(); it++) {
		if (it->second > 1000) {	
			bin[6]++;	// Bin > 1000
		}
		else if (it->second > 200) {
			bin[5]++;	// 1000 => Bin > 200
		}
		else if (it->second > 100) {
			bin[4]++;	// 200 => Bin > 100
		}
		else if (it->second > 5) {
			bin[3]++;	// 100 => Bin > 5
		}
		else if (it->second > 1) {
			bin[2]++;	// 5 => Bin > 1
		}
		else if (it->second == 1) {
			bin[1]++;	// Bin == 1
		}
		else {
			bin[0]++;	// Trash Bin
		}
	}
	writePartTwo(bin, tCount, cCount, eCount, ipBin);
}

void writePartTwo(int *bin, int tC, int cC, int eC, int *ipBin) {

	// Open file
	std::ofstream outFile;
	// outFile.open("output_text_files/partTwo.txt");
    outFile.open("/Users/Jason/Desktop/Xcode/ECE_478/autosys/src/dataset_text_files/partTwo.txt");
    
	// Check that file exists
	if (!outFile) {
		std::cout << "Unable to open file\n";
		exit(1);
	}

	// Variables and output of Graph 2
	int totalBin = bin[0] + bin[1] + bin[2] + bin[3] + bin[4] + bin[5] + bin[6];

	outFile << "\nGraph 2: There were a total of " << totalBin << "entries.\n";
	outFile << "Bin < 1: " << bin[0] << std::endl;
	outFile << "Bin 1: " << bin[1] << std::endl;
	outFile << "Bin 2-5: " << bin[2] << std::endl;
	outFile << "Bin 5-100: " << bin[3] << std::endl;
	outFile << "Bin 100-200: " << bin[4] << std::endl;
	outFile << "Bin 200-1000: " << bin[5] << std::endl;
	outFile << "Bin 1000+: " << bin[6] << std::endl;

	// Variables and output of Graph 3
	// TODO
	outFile << "\nGraph 3: \n\n";
    
    outFile << "Graph 3 total IP entries: " << ipBin[0] + ipBin[1] + ipBin[2] + ipBin[3] + ipBin[4] << std::endl;
    outFile << "Class A (1.0.0.0 to 127.255.255.255): " << ipBin[0] << std::endl;
    outFile << "Class B (128.0.0.0 to 191.255.255.255): " << ipBin[1] << std::endl;
    outFile << "Class C (192.0.0.0 to 223.255.255.255): " << ipBin[2] << std::endl;
    outFile << "Class D (224.0.0.0 to 239.255.255.255): " << ipBin[3] << std::endl;
    outFile << "Class E (240.0.0.0 to 255.255.255.255): " << ipBin[4] << std::endl;

	// Variables and output of Graph 4
	double totalCount = tC + cC + eC;
	double tPercent = (double)tC / totalCount * 100.0;
	double ePercent = (double)eC / totalCount * 100.0;
	double cPercent = (double)cC / totalCount * 100.0;

	outFile << "\nGraph 4: There were a total of " << totalCount << "entries. Of which, the class distribution are as follows:\n";
	outFile << "Transit/Access = " << tC << "\twith a percentage of " << tPercent << std::endl;
	outFile << "Enterprise = " << eC << "\t\twith a percentage of " << ePercent << std::endl;
	outFile << "Content = " << cC << "\t\t\twith a percentage of " << cPercent << std::endl;
	outFile << "\n\n\n";

	outFile.close();

}
