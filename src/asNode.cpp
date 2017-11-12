#include "asNode.h"

Node::Node() {
	this->id = -1;
	this->degree = -1;
}

Node::Node(int id) {
	this->id = id;
	this->degree = -1;
}

void Node::calculateDegree() {
	this->degree = peers.size() + customers.size();
}

void Node::setId(int i) {
	this->id = i;
}

int Node::getId() {
	return this->id;
}

void Node::setDegree(int i) {
	this->degree = i;
}

int Node::getDegree() {
	return this->degree;
}

void Node::addPeer(int i) {
	this->peers.push_back(i);
}

std::vector<int> Node::getPeers() {
	return this->peers;
}

void Node::addCust(int i) {
	this->customers.push_back(i);
}

std::vector<int> Node::getCustomers() {
	return this->customers;
}
