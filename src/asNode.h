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
	Node();
	Node(int val);
	int getId();
	void setDegree(int val);
	int getDegree();
	void addPeer(int AS);
	void addCustomer(int AS);
	std::vector<int> getPeers();
	std::vector<int> getCustomers();
};
#endif // ASNODE_H
