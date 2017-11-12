#include "asTopology_V2.h"

//Temporary, debug time
#include <chrono>
#include <ctime>

void parseIPPrefix(std::multimap<int, int>* p2p, std::multimap<int, int>* p2c, std::multimap<int, int>* ip) {
    std::ifstream inFile;
    inFile.open("/Users/Jason/Desktop/Xcode/ECE_478/autosys/src/dataset_text_files/routeviews-rv6-20171110-1200.pfx2as.txt");
    
    if (!inFile) {
        std::cout << "Unable to open file\n";
        exit(1);
    }
    
    std::string inLine;
    std::string prefix, length, AS;
    while (std::getline(inFile, inLine)) {
        std::stringstream iss;
        std::vector<std::string> temp;
        iss << inLine;
        iss >> prefix >> length >> AS;
    }
    
    
}

void parsePartTwo(std::multimap<int, int>* p2p, std::multimap<int, int>* p2c) {
	// Temp Node vector
	// std::vector< std::vector<int> > returnNodeVec;

	// Open file
	std::ifstream inFile;
	// inFile.open("dataset_text_files/20170901.as-rel2.txt");
    inFile.open("/Users/Jason/Desktop/Xcode/ECE_478/autosys/src/dataset_text_files/20170901.as-rel2.txt");

	// Check that file exists
	if (!inFile) {
		std::cout << "Unable to open file\n";
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

std::map<int, Node *> processPartTwo(std::vector< std::vector<int> > nodeUnsorted) {
	// Temp Node vector
	std::map<int, Node *> returnNodeVec;
	Node temp;
	int index = 0;
	// TEMPORARY
	auto start = std::chrono::system_clock::now();
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds;
	int j = 0;

	for (unsigned int i = 0; i < nodeUnsorted.size(); i++) {
		Node* entryOne = returnNodeVec[nodeUnsorted.at(i).at(0)];
		Node* entryTwo = returnNodeVec[nodeUnsorted.at(i).at(1)];
		if (entryOne == NULL) {
			Node *newNode = new Node(nodeUnsorted.at(i).at(0)); // Makes new node w/ id of source
			returnNodeVec[nodeUnsorted.at(i).at(0)] = newNode;	// I realize that id is redudant now that we
			entryOne = returnNodeVec[nodeUnsorted.at(i).at(0)]; // are using maps but I don't feel like changing it
		}
		if (entryTwo == NULL) {
			Node *newNode = new Node(nodeUnsorted.at(i).at(1)); // Makes new node w/ id of target
			returnNodeVec[nodeUnsorted.at(i).at(1)] = newNode;  // I realize that id is redudant now that we
			entryTwo = returnNodeVec[nodeUnsorted.at(i).at(1)]; // are using maps but I don't feel like changing it
		}

		if (nodeUnsorted.at(i).at(2) == 0) { // p2p
			entryOne->addPeer(nodeUnsorted.at(i).at(1));
			entryTwo->addPeer(nodeUnsorted.at(i).at(0));
		}
		else if (nodeUnsorted.at(i).at(2) == -1) { // p2c
			entryOne->addCust(nodeUnsorted.at(i).at(1));
		}
	}
	return returnNodeVec;
}

bool checkSourceField(std::vector<Node> nodeList, int id) {
	for (unsigned i = 0; i < nodeList.size(); i++) {
		if (nodeList.at(i).getId() == id) {
			return true;
		}
	}
	return false;
}

bool checkTargetField(std::vector<Node> nodeList, int id) {
	for (unsigned i = 0; i < nodeList.size(); i++) {
		if (nodeList.at(i).getId() == id) {
			return true;
		}
	}
	return false;
}

int findNodeIndex(std::vector<Node> nodeList, int id) {
	for (unsigned i = 0; i < nodeList.size(); i++) {
		if (nodeList.at(i).getId() == id) {
			return i;
		}
	}
}

/*


	int state = 0, indexA, indexB;
	checkNode(firstNode, nodes) ? state = state : state += 2;
	checkNode(secondNode, nodes) ? state = state : state += 1;
	Node nodeA(firstNode);
	Node nodeB(secondNode);
	switch (state) {
	case 0: // firstNode in list, secondNode in list
		indexA = findNode(firstNode, nodes);
		indexB = findNode(secondNode, nodes);
		if (type == 0) { // Peer to Peer
			nodes.at(indexA).addPeer(secondNode);
			nodes.at(indexB).addPeer(firstNode);
		}
		else if (type == -1) { // Provider to Customer
			nodes.at(indexA).addCustomer(secondNode);
		}
		break;
	case 1: // firstNode in list, secondNode NOT in list
		indexA = findNode(firstNode, nodes);
		if (type == 0) { // Peer to Peer
			nodes.at(indexA).addPeer(secondNode);
			nodeB.addPeer(firstNode);
			nodes.push_back(nodeB);
		}
		else if (type == -1) { // Provider to Customer
			nodes.at(indexA).addCustomer(secondNode);
		}
		break;
	case 2: // firstNode NOT in list, secondNode in list
		indexB = findNode(secondNode, nodes);
		if (type == 0) { // Peer to Peer
			nodeA.addPeer(secondNode);
			nodes.push_back(nodeA);
			nodes.at(indexB).addPeer(firstNode);
		}
		else if (type == -1) { // Provider to Customer
			nodeA.addCustomer(secondNode);
			nodes.push_back(nodeA);
		}
		break;
	case 3: // firstNode NOT in list, secondNode NOT in list
		if (type == 0) { // Peer to Peer
			nodeA.addPeer(secondNode);
			nodeB.addPeer(firstNode);
			nodes.push_back(nodeA);
			nodes.push_back(nodeB);
		}
		else if (type == -1) { // Provider to Customer
			nodeA.addCustomer(secondNode);
			nodes.push_back(nodeA);
		}
		break;
	}

*/
