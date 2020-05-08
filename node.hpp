#ifndef __NODE_HPP__
#define __NODE_HPP__

#include <string>
#include "problem.hpp"
class Node
{
	public:
		Node(Problem* problem, Node* node, std::string mode);
		~Node();
		Node* getParent();
		Problem* getProblem();
		double getDepth();
		double getCostH();
		double getCost();
	private:
		Node* parent;
		Problem* problem;
		double costH;
		double depth;
};

#endif
