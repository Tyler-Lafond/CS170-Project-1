#include <iostream>
#include "problem.hpp"
#include "tree.hpp"

using namespace std;

bool rowInputs(int* customPuzzle);

void print(list<Node*> sol, int nodesExpanded, int maxSize, string mode);

int main()
{
	bool valid = false;
	string choice;
	string mode;
	int defaultPuzzle[DIMENSION_SIZE][DIMENSION_SIZE] = {{1, 0, 3}, {4, 2, 6}, {7, 5, 8}};
	int customPuzzle[DIMENSION_SIZE][DIMENSION_SIZE];
	int* defaultPuzPointer = &defaultPuzzle[0][0];
	int* customPuzPointer = &customPuzzle[0][0];
	Problem* problem;
	//interface

	cout << "Welcome to 862139091's 8 puzzle solver." << endl;
	cout << "Type \"1\" to use a default puzzle, or \"2\" to enter your own puzzle." << endl;
	while (!valid)
	{
		getline(cin, choice, '\n');
		if (choice == "1")
		{	
			valid = true;
		}
		else if (choice == "2")
		{
			cout << "Enter your puzzle, use a zero to represent the blank." << endl;
			valid = rowInputs(customPuzPointer);
		}
		else
		{
			cout << "Error. Invalid input. Please try again." << endl;
		}
	}

	if (choice == "1")
	{
		problem = new Problem(defaultPuzPointer);
	}
	else if (choice == "2")
	{
		problem = new Problem(customPuzPointer);
	}

	choice = "";
	valid = false;
	problem->print();

	while (!valid)
	{
		cout << "Please select the algorithm you would like to use by entering the associated number:" << endl;
		cout << "1. Uniform Cost Search" << endl;
		cout << "2. A* with the Misplaced Tile heuristic" << endl;
		cout << "3. A* with the Euclidean distance heuristic" << endl;
		getline(cin, choice, '\n');
		if (choice == "1")
		{
			mode = "Uniform";
			valid = true;
		}
		else if (choice == "2")
		{
			mode = "Misplaced";
			valid = true;
		}
		else if (choice == "3")
		{
			mode = "Euclidean";
			valid = true;
		}
		else
		{
			cout << "Error. Invalid input. Please try again." << endl;
		}
	}
	//problem
	Tree tree = Tree(problem, mode);
	cout << endl;
	list<Node*> solution = tree.search();
	if (!solution.empty())
	{
		print(solution, tree.getNodesExpanded(), tree.getMaxSize(), mode);
	}
	delete problem;
	problem = 0;
	
	return 0;
}

bool rowInputs(int* customPuzzle)
{
	int counter = 0;
	std::string rowInput;
	bool valid = false;
	while (!valid)
	{
		for (int i = 1; i < DIMENSION_SIZE + 1; i++)
		{
			counter = 0;
			cout << "Enter row " << i << ", use spaces or tabs between the numbers:" << endl;
			getline(cin, rowInput, '\n');
			for (int j = 0; j < rowInput.length(); j++)
			{
				if ((rowInput[j] > '8' && rowInput[j] < '0') && rowInput[j] != ' ')
				{
					cout << "Error. Invalid input. Please try again." << endl;
					break;
				}
				else if (rowInput[j] < '9' && rowInput[j] >= '0')
				{
					customPuzzle[(i-1) * DIMENSION_SIZE + counter] = rowInput[j] - '0';
					counter++;
				}
			}

			if (counter == DIMENSION_SIZE)
			{
				valid = true;
			}
			else
			{
				cout << "Error. Invalid input. Please try again." << endl;
			}

			if (!valid)
			{
				i--;
			}
			else if (i != DIMENSION_SIZE)
			{
				valid = false;
			}
		}
	}

	return valid;
}

void print(list<Node*> sol, int nodesExpanded, int maxSize, string mode)
{
	cout << "Expanding state" << endl;
	for (list<Node*>::iterator iter = sol.begin(); iter != sol.end(); iter++)
	{
		(*iter)->getProblem()->print();
		cout << "Expanding this node..." << endl;
		cout << endl;
		if ((*iter)->getCostH() > 0 || mode == "Uniform")
		{
			cout << "The best state to expand with g(n) = " << (*iter)->getDepth();
			cout <<" and h(n) = " << (*iter)->getCostH();
			cout << " is..." << endl;
		}
	}
	cout << "Goal reached" << endl;
	cout << endl;
	cout << "To solve this problem the search algorithm expanded a total of " << nodesExpanded << " nodes." << endl;
	cout << "The maximum number of nodes in the queue at any one time: " << maxSize << "." << endl;
}
