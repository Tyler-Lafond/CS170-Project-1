#include <iostream>
#include "problem.hpp"

Problem::Problem(int puzzle[][3][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			this->puzzle[i][j] = *puzzle[i][j];
		}
	}
}

Problem::~Problem()
{
}

int* Problem::getPuzzle()
{
	int* currPuzzle = *puzzle;
	return currPuzzle;
}

void Problem::swap(std::pair <int, int> blank, std::pair <int, int> tile)
{
	int temp = puzzle[blank.first][blank.second];
	puzzle[blank.first][blank.second] = puzzle[tile.first][tile.second];
	puzzle[tile.first][tile.second] = temp;
}

int Problem::evaluate()
{
	int cost = 0;
	int values[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
	bool found = false;

	for (int i = 0; i < 9; i++)
	{
		found = false;
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				if (puzzle[j][k] == values[i])
				{
					int diffX = k - i % 3;
					int diffY = j - i / 3;
					cost += abs(diffX) + abs(diffY);
				}
			}
		}
	}

	return cost;
}

bool Problem::compare(Problem* problem)
{
	int* puzzleB = problem->getPuzzle();
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (puzzle[i][j] != puzzleB[i * 3 + j])
			{
				return false;
			}
		}
	}

	return true;
}
