#include <iostream>
#include "problem.hpp"
#include "tree.hpp"

using namespace std;

int main()
{
	int puzzle[3][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}};
	//interface
	Problem* probA = new Problem(&puzzle);
	bool match = probA->compare(probA);
	cout << match << endl;
	delete probA;
	probA = 0;
	//problem
	
	return 0;
}
