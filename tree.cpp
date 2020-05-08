#include <iostream>
#include "tree.hpp"

Tree::Tree(Problem* problem, std::string mode)
{
	nodesExpanded = 0;
	maxSize = 0;
	Node* nullPtr = 0;
	root = new Node(problem, nullPtr, mode);
	frontier.push_back(root);
	this->mode = mode;
}

Tree::~Tree()
{
	for (std::list<Node*>::iterator iter = explored.begin(); iter != explored.end(); iter++)
	{
		delete *iter;
		*iter = 0;
	}
	explored.clear();
}

int Tree::getNodesExpanded()
{
	return nodesExpanded;
}

int Tree::getMaxSize()
{
	return maxSize;
}

void Tree::addNode(Node* node)
{
	bool inserted = false;
	for (std::list<Node*>::iterator iter = frontier.begin(); iter != frontier.end(); iter++)
	{
		if (node->getCost() < (*iter)->getCost())
		{
			frontier.insert(iter, node);
			inserted = true;
			break;
		}
	}
	if (inserted == false)
	{
		frontier.push_back(node);
	}

}

std::list<Node*> Tree::search()
{
	std::list<Node*> solution;
	bool found = false;
	while(frontier.empty() == false && found == false)
	{
		std::list<Node*>::iterator iter = frontier.begin();
		frontier.pop_front();
		if (checkGoal(*iter))
		{
			found = true;
			Node* temp = *iter;
			while (temp != 0)
			{
				solution.push_front(temp);
				temp = temp->getParent();
			}
			frontier.clear();
			explored.push_back(*iter); //to help delete final node when program is done
		}

		else
		{
			explored.push_back(*iter);
			expandNode(*iter);
			nodesExpanded++;
			if (frontier.size() > maxSize)
			{
				maxSize = frontier.size();
			}
		}
	}

	if (!found)
	{
		std::cout << "No solution found" << std::endl;
	}

	return solution;
}

void Tree::expandNode(Node* node)
{
	std::pair <int, int> blank;
	std::pair <int, int> tile;
	int tempPuzzle[DIMENSION_SIZE][DIMENSION_SIZE];
	int* tempPuzPointer = node->getProblem()->getPuzzle();
	Problem* tempProblem = 0;
	bool found = false;

	for (int i = 0; i < DIMENSION_SIZE; i++)
	{
		for (int j = 0; j < DIMENSION_SIZE; j++)
		{
			tempPuzzle[i][j] = tempPuzPointer[i * DIMENSION_SIZE + j];
		}
	}

	tempPuzPointer = 0;

	for (int i = 0; i < DIMENSION_SIZE; i++)
	{
		found = false;
		for (int j = 0; j < DIMENSION_SIZE; j++)
		{
			if (tempPuzzle[i][j] == 0)
			{
				if (j > 0)
				{
					tempProblem = new Problem(*tempPuzzle);
					blank = std::make_pair(i, j);
					tile = std::make_pair(i, j-1);
					tempProblem->swap(blank, tile);
					
					checkLists(tempProblem, node, blank, tile);
				}

				if (j < DIMENSION_SIZE - 1)
				{
					tempProblem = new Problem(*tempPuzzle);
					blank = std::make_pair(i, j);
					tile = std::make_pair(i, j+1);
					tempProblem->swap(blank, tile);
					
					checkLists(tempProblem, node, blank, tile);
				}

				if (i > 0)
				{
					tempProblem = new Problem(*tempPuzzle);
					blank = std::make_pair(i, j);
					tile = std::make_pair(i-1, j);
					tempProblem->swap(blank, tile);
					
					checkLists(tempProblem, node, blank, tile);
				}

				if (i < DIMENSION_SIZE - 1)
				{
					tempProblem = new Problem(*tempPuzzle);
					blank = std::make_pair(i, j);
					tile = std::make_pair(i+1, j);
					tempProblem->swap(blank, tile);
					
					checkLists(tempProblem, node, blank, tile);
				}
				tempProblem = 0;
				break;
			}
		}
		if (found)
		{
			break;
		}
	}
}

void Tree::checkLists(Problem* problem, Node* node, std::pair<int, int> blank, std::pair<int, int> tile)
{
	bool found = false;
	Node* newNode;
	for (std::list<Node*>::iterator iter = frontier.begin(); iter != frontier.end(); iter++)
	{
		if (problem->compare((*iter)->getProblem()) == true)
		{
			found = true;
			break;
		}
	}

	if (found == false)
	{
		for (std::list<Node*>::iterator iter = explored.begin(); iter != explored.end(); iter++)
		{
			if (problem->compare((*iter)->getProblem()) == true)
			{
				found = true;
				break;
			}
		}
	}

	if (found == false)
	{
		newNode = new Node(problem, node, mode);
		if (frontier.empty())
		{
			frontier.push_back(newNode);
		}
		else
		{
			addNode(newNode);
			newNode = 0;
		}
	}
	else
	{
		delete problem;
		problem = 0;
	}
}

bool Tree::checkGoal(Node* node)
{
	int* tempPuzPointer = node->getProblem()->getPuzzle();
	for (int i = 0; i < DIMENSION_SIZE; i++)
	{
		for (int j = 0; j < DIMENSION_SIZE; j++)
		{
			if (goalState[i][j] != tempPuzPointer[i * DIMENSION_SIZE + j])
			{
				tempPuzPointer = 0;
				return false;
			}
		}
	}

	tempPuzPointer = 0;
	return true;
}

