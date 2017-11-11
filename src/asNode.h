#ifndef ASNODE_H
#define ASNODE_H

#include <iostream>
#include <vector>

class Node {
private:
	int id;
	int degree;
	std::vector<int> peers;
	std::vector<int> customers;
public:
	// Constructor
	Node();

	// Methods
	void calculateDegree();

	// Getters/Setters
	void setId(int i);
	int getId();
	void setDegree(int i);
	int getDegree();
	void addPeer(int i);
	std::vector<int> getPeers();
	void addCust(int i);
	std::vector<int> getCustomers();
};
#endif // ASNODE_H
