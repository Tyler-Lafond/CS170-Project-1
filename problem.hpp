#ifndef __PROBLEM_HPP__
#define __PROBLEM_HPP__

#include <utility>
#include <cstdlib>
class Problem
{
	public:
		Problem(int puzzle[][3][3]);
		~Problem();
		int* getPuzzle();
		void swap(std::pair <int, int> blank, std::pair <int, int> tile);
		int evaluate();
		bool compare(Problem* problem);
	private:
		int puzzle[3][3];
};

#endif
