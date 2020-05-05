#ifndef __PROBLEM_HPP__
#define __PROBLEM_HPP__

#include <utility>
#include <cstdlib>

const int DIMENSION_SIZE = 3;

class Problem
{
	public:
		Problem(int* puzzle);
		~Problem();
		int* getPuzzle();
		void swap(std::pair <int, int> blank, std::pair <int, int> tile);
		int evaluate();
		bool compare(Problem* problem);
		void print();
	private:
		int puzzle[DIMENSION_SIZE][DIMENSION_SIZE];
};

#endif
