#include "asTopology_V2.h"

std::vector< std::vector<int> > parsePartTwo() {
	// Temp Node vector
	std::vector< std::vector<int> > returnNodeVec;

	// Open file
	std::ifstream inFile;
	inFile.open("dataset_text_files/20170901.as-rel2.txt");

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
		std::vector<int> temp;
		iss << inLine;
		iss >> x1 >> pipeThrow >> x2 >> pipeThrow >> t;
		temp.push_back(x1);
		temp.push_back(x2);
		temp.push_back(t);
		returnNodeVec.push_back(temp);
	}

	// Close file and return unsorted node list
	inFile.close();
	return returnNodeVec;
}

std::vector<Node> processPartTwo(std::vector< std::vector<int> > nodeUnsorted) {
	// Temp Node vector
	std::vector<Node> returnNodeVec;
	Node temp;
	int index = 0;
	for (unsigned int i = 0; i < nodeUnsorted.size(); i++) {
		
		// Process source node
		if (!checkSourceField(returnNodeVec, nodeUnsorted.at(i).at(0))) {
			temp.setId(nodeUnsorted.at(i).at(0));
			temp.getPeers().clear();
			temp.getCustomers().clear();
			returnNodeVec.push_back(temp);
		}
		index = findNodeIndex(returnNodeVec, nodeUnsorted.at(i).at(0));

		if (nodeUnsorted.at(i).at(2) == 0) { // p2p
			returnNodeVec.at(index).addPeer(nodeUnsorted.at(i).at(1));
		}
		else if (nodeUnsorted.at(i).at(2) == -1) { // p2c
			returnNodeVec.at(index).addCust(nodeUnsorted.at(i).at(1));
		}
		

		// Process target node
		if (!checkTargetField(returnNodeVec, nodeUnsorted.at(i).at(1))) {
			temp.setId(nodeUnsorted.at(i).at(1));
			temp.getPeers().clear();
			temp.getCustomers().clear();
			returnNodeVec.push_back(temp);
		}
		index = findNodeIndex(returnNodeVec, nodeUnsorted.at(i).at(1));

		if (nodeUnsorted.at(i).at(2) == 0) { // p2p
			returnNodeVec.at(index).addPeer(nodeUnsorted.at(i).at(0));
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