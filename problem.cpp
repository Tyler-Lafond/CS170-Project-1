#include <iostream>
#include <math.h>
#include "problem.hpp"

Problem::Problem(int* puzzle)
{
	for (int i = 0; i < DIMENSION_SIZE; i++)
	{
		for (int j = 0; j < DIMENSION_SIZE; j++)
		{
			this->puzzle[i][j] = puzzle[i * DIMENSION_SIZE + j];
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

double Problem::evaluate(std::string mode)
{
	double cost = 0;
	int counter = 0;
	int size = DIMENSION_SIZE * DIMENSION_SIZE;
	int values[size] = {1, 2, 3, 4, 5, 6, 7, 8, 0};
	bool found = false;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < DIMENSION_SIZE; j++)
		{
			for (int k = 0; k < DIMENSION_SIZE; k++)
			{
				if (puzzle[j][k] == values[i])
				{
					if (mode == "Misplaced")
					{
						if(j != (i / 3) || k != (i % 3))
						{
							if (counter < DIMENSION_SIZE * DIMENSION_SIZE - 1)
							{
								cost++;
							}
							counter++;
						}
					}
					else if (mode == "Euclidean")
					{
						if (counter < DIMENSION_SIZE * DIMENSION_SIZE - 1)
						{
							cost += sqrt(pow(static_cast<double>(j) - static_cast<double>(i/3), 2.0) + pow(static_cast<double>(k) - static_cast<double>(i%3), 2.0));
						}
						counter++;
					}
					break;
				}
			}
		}
	}

	return cost;
}

bool Problem::compare(Problem* problem)
{
	int* puzzleB = problem->getPuzzle();
	for (int i = 0; i < DIMENSION_SIZE; i++)
	{
		for (int j = 0; j < DIMENSION_SIZE; j++)
		{
			if (puzzle[i][j] != puzzleB[i * DIMENSION_SIZE + j])
			{	
				puzzleB = 0;
				return false;
			}
		}
	}

	puzzleB = 0;
	return true;
}

void Problem::print()
{
	for (int i = 0; i < DIMENSION_SIZE; i++)
	{
		for (int j = 0; j < DIMENSION_SIZE; j++)
		{
			if (puzzle[i][j] == 0)
			{
				std::cout << "b ";
			}
			else
			{
				std::cout << puzzle[i][j] << " ";
			}
		}
		std::cout << std::endl;
	}
}
