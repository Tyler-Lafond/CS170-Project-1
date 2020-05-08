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
		int getNodesExpanded();
		int getMaxSize();
		void addNode(Node* node);
		std::list<Node*> search();
		void expandNode(Node* node);
		void checkLists(Problem* problem, Node* node, std::pair<int, int> blank, std::pair<int, int> tile);
		bool checkGoal(Node* node);
	private:
		int nodesExpanded;
		int maxSize;
		int goalState[DIMENSION_SIZE][DIMENSION_SIZE] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
		Node* root;
		std::list<Node*> frontier;
		std::list<Node*> explored;
		std::string mode;

};

#endif
