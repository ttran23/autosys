#include "asNode.h"

Node::Node() {
	this->id = -1;
	this->degree = -1;
}

Node::Node(int val) {
	this->id = val;
	this->degree = -1;
}

int Node::getId() {
	return this->id;
}

void Node::setDegree(int val) {
	this->degree = val;
}

int Node::getDegree() {
	return this->degree;
}

void Node::addPeer(int AS) {
	bool found = false;
	for (int i = 0; i < this->peers.size(); i++) {
		if (peers.at(i) == AS) {
			found = true;
			break;
		}
	}
	if (!found) {
		this->peers.push_back(AS);
	}
}

void Node::addCustomer(int AS) {
	bool found = false;
	for (int i = 0; i < this->customers.size(); i++) {
		if (customers.at(i) == AS) {
			found = true;
			break;
		}
	}
	if (!found) {
		this->customers.push_back(AS);
	}
}

std::vector<int> Node::getPeers() {
	return this->peers;
}

std::vector<int> Node::getCustomers() {
	return this->customers;
}
