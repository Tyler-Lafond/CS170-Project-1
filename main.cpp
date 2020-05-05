#include <iostream>
#include "problem.hpp"
#include "tree.hpp"

using namespace std;

int main()
{
	int puzzle1[3][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}};
	int puzzle2[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 0, 8}};
	int* puz1 = &puzzle1[0][0];
	int* puz2 = &puzzle2[0][0];
	//interface
	Problem* probA = new Problem(puz1);
	Problem* probB = new Problem(puz2);
	pair <int, int> coord1;
	pair <int, int> coordBlank;
	coord1 = make_pair(0, 1);
	coordBlank = make_pair(0, 0);
	probA->swap(coordBlank, coord1);
	bool match = probA->compare(probB);
	int cost = probB->evaluate();
//	cout << cost << endl;
	probB->print();
	delete probA;
	delete probB;
	probA = 0;
	probB = 0;
	//problem
	
	return 0;
}
