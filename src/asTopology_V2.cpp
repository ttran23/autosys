#include "asTopology_V2.h"

std::vector<Node> parseFile2() {
	std::vector<Node> nodes;

	// Open file
	std::ifstream inFile;
	inFile.open("dataset_text_files/20170901.as-rel2.txt");
	// Check that file exists
	if (!inFile) {
		std::cout << "Unable to open file\n";
		exit(1);
	}
	int itr = 0;
	// Get each line
	std::string inLine;
	int firstNode, secondNode, type;
	char pipeThrow;
	while (std::getline(inFile, inLine)) {
		if (inLine.at(0) == '#')
			continue;
		std::stringstream iss;
		iss << inLine;
		iss >> firstNode >> pipeThrow >> secondNode >> pipeThrow >> type;
		std::cout << itr++ << std::endl;
		std::cout << iss.str() << std::endl;
		std::cout << firstNode << "  " << secondNode << "  " << type << "\n\n";
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
	}
	return nodes;
}

bool checkNode(int nodeCurrent, std::vector<Node> nodeList) {
	for (unsigned int i = 0; i < nodeList.size(); i++) {
		if (nodeList.at(i).getId() == nodeCurrent) {
			return true;
		}
	}
	return false;
}

int findNode(int nodeCurrent, std::vector<Node> nodeList) {
	for (unsigned int i = 0; i < nodeList.size(); i++) {
		if (nodeList.at(i).getId() == nodeCurrent) {
			return i;
		}
	}
}

void calculateData(std::vector<int> node) {

}