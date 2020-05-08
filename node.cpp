#include <iostream>
#include "node.hpp"

Node::Node(Problem* problem, Node* node, std::string mode)
{
	this->problem = problem;
	parent = node;
	if (parent == 0)
	{
		depth = 0.0;
	}
	else
	{
		depth = parent->getDepth();
		depth++;
	}

	if (mode == "Misplaced" || mode == "Euclidean")
	{
		costH = getProblem()->evaluate(mode);
	}
	else
	{
		costH = 0.0;
	}
}

Node::~Node()
{
	delete problem;
	problem = 0;
}

Node* Node::getParent()
{
	return parent;
}

Problem* Node::getProblem()
{
	return problem;
}

double Node::getDepth()
{
	return depth;
}

double Node::getCostH()
{
	return costH;
}

double Node::getCost()
{
	return depth + costH;
}
