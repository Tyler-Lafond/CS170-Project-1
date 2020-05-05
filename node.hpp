#ifndef __NODE_HPP__
#define __NODE_HPP__

#include "problem.hpp"
class Node
{
	public:
		Node(Problem* problem);
		void getProblem();
	private:
		Node* parent;
		Problem* problem;
};

#endif
