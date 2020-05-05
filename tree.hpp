#ifndef __TREE_HPP__
#define __TREE_HPP__

#include <string>
#include <list>
#include "node.hpp"

class Tree
{
	public:
		Tree(Problem* problem, std::string mode);
		~Tree();
		void expandNode(Node* node);

	private:
		Node* root;
		std::list<Node*> frontier;
		std::list<Node*> explored;
		std::string mode;

};

#endif
