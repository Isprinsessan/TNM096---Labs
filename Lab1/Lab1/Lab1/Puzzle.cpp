#include "stdafx.h"
#include "Puzzle.h"
#include <string>


Puzzle::Puzzle()
{
	Node startPuzzle;

	//Starting puzzles
	//Hard one, 27 steps
	startPuzzle.puzzleState[0] = 1; startPuzzle.puzzleState[1] = 0; startPuzzle.puzzleState[2] = 5;
	startPuzzle.puzzleState[3] = 6; startPuzzle.puzzleState[4] = 4; startPuzzle.puzzleState[5] = 7;
	startPuzzle.puzzleState[6] = 2; startPuzzle.puzzleState[7] = 3; startPuzzle.puzzleState[8] = 8;
	
	//Less hard
	//startPuzzle.puzzleState[0] = 4; startPuzzle.puzzleState[1] = 1; startPuzzle.puzzleState[2] = 2;
	//startPuzzle.puzzleState[3] = 5; startPuzzle.puzzleState[4] = 8; startPuzzle.puzzleState[5] = 3;
	//startPuzzle.puzzleState[6] = 0; startPuzzle.puzzleState[7] = 7; startPuzzle.puzzleState[8] = 6;

	//Create goal puzzle
	goalState.puzzleState[0] = 1; goalState.puzzleState[1] = 2; goalState.puzzleState[2] = 3;
	goalState.puzzleState[3] = 4; goalState.puzzleState[4] = 5; goalState.puzzleState[5] = 6;
	goalState.puzzleState[6] = 7; goalState.puzzleState[7] = 8; goalState.puzzleState[8] = 0;

	startPuzzle.g = 0;

	//startPuzzle.h = GetHCost(startPuzzle);
	startPuzzle.h = ManhattanSum(startPuzzle);
	startPuzzle.f = startPuzzle.h + startPuzzle.g;

	//Push the starting node to the open set
	openSet.push(startPuzzle);

}

void Puzzle::MoveEmpty() 
{
	int nrOfMoves = 0;
	std::string currentBoardLabel = "";

	while (true)
	{
		//Create the label for the node
		currentBoardLabel = createKey(openSet.top());

		//Insert the node into the map with the corresponding label
		closedSet.insert({ currentBoardLabel, openSet.top() });

		//Collect the latest used node from the closed set
		latestNode = &closedSet.at(currentBoardLabel);

		//Remove it from the open set
		openSet.pop();

		//Find the empty tile and use it to see possible ways to move
		int empty = FindEmpty(*latestNode);

		switch (empty){
		case 0:
			//If the empty node is in the top left
			MoveTile(empty, 1);	//Right
			MoveTile(empty, 3);	//Down
			break;
		case 1:
			//If the empty node is in the top middle
			MoveTile(empty, 0);	//Left
			MoveTile(empty, 2);	//Right
			MoveTile(empty, 4); //Down
			break;
		case 2:
			//If the empty node is in the top right
			MoveTile(empty, 1);	//Left
			MoveTile(empty, 5);	//Down
			break;
		case 3:
			//If the empty node is in the middle left
			MoveTile(empty, 0);	//Up
			MoveTile(empty, 4);	//Right
			MoveTile(empty, 6);	//Down
			break;
		case 4:
			//If the empty node is in the middle middle
			MoveTile(empty, 1);	//Up
			MoveTile(empty, 3);	//Left
			MoveTile(empty, 5);	//Right
			MoveTile(empty, 7);	//Down
			break;
		case 5:
			//If the empty node is in the top right
			MoveTile(empty, 2);	//Up
			MoveTile(empty, 4);	//Right
			MoveTile(empty, 8);	//Down
			break;
		case 6:
			//If the empty node is in the bottom left
			MoveTile(empty, 3);	//Up
			MoveTile(empty, 7);	//Right
			break;
		case 7:
			//If the empty node is in the bottom middle
			MoveTile(empty, 4);	//Up
			MoveTile(empty, 6);	//Left
			MoveTile(empty, 8);	//Right
			break;
		case 8:
			//If the empty node is in the bottom right
			MoveTile(empty, 5);	//Up
			MoveTile(empty, 7);	//Left
			break;
		}

		nrOfMoves++;

		//If the puzzle is solved or if the open set is empty, break the loop
		if (ComparePuzzles(openSet.top(), goalState) || openSet.empty())
			break;
	}

	std::cout << std::endl << "This took " << nrOfMoves << " moves." << std::endl;
}

void Puzzle::MoveTile(int _start, int _end)
{
	//Create a new puzzle node that inherits all properites of the latest puzzle
	Node newPuzzle;

	for (int i = 0; i < 9; i++)
		newPuzzle.puzzleState[i] = latestNode->puzzleState[i];

	//Change the g, h and f for the new puzzle
	newPuzzle.g = latestNode->g + 1;

	//Get h cost with either number of wrong tiles or with Manhattan distance
	//newPuzzle.h = GetHCost(newPuzzle);
	newPuzzle.h = ManhattanSum(newPuzzle);

	//Move the tile and create a new puzzle
	newPuzzle.puzzleState[_start] = newPuzzle.puzzleState[_end];
	newPuzzle.puzzleState[_end] = 0;

	newPuzzle.f = newPuzzle.g + newPuzzle.h;

	//If the new puzzle is not in the closed set, add it to the open set
	if (!NodeInSet(newPuzzle))
		openSet.push(newPuzzle);
}

int Puzzle::FindEmpty(Node _node)
{
	for (int i = 0; i < 9; i++)
	{
		if (_node.puzzleState[i] == 0)
			return i;
	}

	return 0;
}

int Puzzle::ManhattanSum(Node _node)
{
	int manhattanSum = 0;

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			//Find the node with the same value to and use their position in the puzzle to calculate manhattan distance
			if (_node.puzzleState[i] == goalState.puzzleState[j])
				manhattanSum += ManhattanDistance(i, j);
		}
	}

	return manhattanSum;
}

int Puzzle::ManhattanDistance(int _position1, int _position2)
{
	//Create two coordinates to compare distance between
	int x1 = _position1 % 3;	//Column
	int y1 = _position1 / 3;	//Row

	int x2 = _position2 % 3;	//Column
	int y2 = _position2 / 3;	//Row

	//Return manhattan distance
	return (abs(x1 - x2) + abs(y1 - y2));
}

int Puzzle::GetHCost(Node _node)
{
	int h = 0;
	for (int i = 0; i < 9; i++)
	{
		if (_node.puzzleState[i] != goalState.puzzleState[i])
			h++;
	}
	return h;
}

bool Puzzle::ComparePuzzles(Node _node1, Node _node2)
{
	for (int i = 0; i < 9; i++)
	{
		if (_node1.puzzleState[i] != _node2.puzzleState[i])
			return false;
	}

	return true;

}

bool Puzzle::NodeInSet(Node _node)
{
	//Search for the key in the closed set, if it is not found, the node is not in the set
	if (closedSet.find(createKey(_node)) == closedSet.end())
		return false;
	else
		return true;
}

std::string Puzzle::createKey(Node _node)
{
	std::string temp = "";

	//Create a key consisting of the numbers in the puzzle
	for (int i = 0; i < 9; i++)
		temp += _node.puzzleState[i];

	return temp;
}

void Puzzle::print()
{
	std::cout << openSet.top().puzzleState[0] << "  " << openSet.top().puzzleState[1] << "  " << openSet.top().puzzleState[2] << std::endl;
	std::cout << openSet.top().puzzleState[3] << "  " << openSet.top().puzzleState[4] << "  " << openSet.top().puzzleState[5] << std::endl;
	std::cout << openSet.top().puzzleState[6] << "  " << openSet.top().puzzleState[7] << "  " << openSet.top().puzzleState[8] << std::endl;
	std::cout << "f: " << openSet.top().f << std::endl;
	std::cout << "g: " << openSet.top().g << std::endl;
	std::cout << "h: " << openSet.top().h << std::endl;
	std::cout << "Moves made: " << openSet.top().g << std::endl;
 
}