#include "stdafx.h"
#include "Node.h"
#include <iostream>
#include <string>

using namespace std;
EightPuzzle::EightPuzzle()
{
	Node puzzleNode;

	puzzleNode.PuzzleState[0] = 6;
	puzzleNode.PuzzleState[1] = 4;
	puzzleNode.PuzzleState[2] = 7;
	puzzleNode.PuzzleState[3] = 8;
	puzzleNode.PuzzleState[4] = 5;
	puzzleNode.PuzzleState[5] = 0;
	puzzleNode.PuzzleState[6] = 3;
	puzzleNode.PuzzleState[7] = 2;
	puzzleNode.PuzzleState[8] = 1;

	goalState.PuzzleState[0] = 1;
	goalState.PuzzleState[1] = 2;
	goalState.PuzzleState[2] = 3;
	goalState.PuzzleState[3] = 4;
	goalState.PuzzleState[4] = 5;
	goalState.PuzzleState[5] = 6;
	goalState.PuzzleState[6] = 7;
	goalState.PuzzleState[7] = 8;
	goalState.PuzzleState[8] = 0;

	puzzleNode.g = 0;
	puzzleNode.h = puzzleNode.f_cost = WrongPositions(puzzleNode); //manhattan or WrongPosition

	openNodes.push(puzzleNode);
	//keyGen(puzzleNode);
}

void EightPuzzle::PuzzleSolver()
{
	int moveCounter = 0;
	string currBoardLabel = "";
	while (true)
	{
		currBoardLabel = keyGen(openNodes.top());
		expTree.insert({ currBoardLabel,openNodes.top() });
		lastExpBranch = &expTree.at(currBoardLabel);

		openNodes.pop();


		// r = right, l = left, u = up , d = down;
		//Depending on where the zero is we move differently after this switch case statement.
		switch (findEmpty(*lastExpBranch))
		{
		case 0:
			moveZero(0, 1, 'r');
			moveZero(0, 3, 'd');
			break;
		case 1:
			moveZero(1, 2, 'r');
			moveZero(1, 4, 'd');
			moveZero(1, 0, 'l');
			break;
		case 2:
			moveZero(2, 1, 'l');
			moveZero(2, 5, 'd');
			break;
		case 3:
			moveZero(3, 4, 'r');
			moveZero(3, 6, 'd');
			moveZero(3, 0, 'u');
			break;
		case 4:
			moveZero(4, 3, 'r');
			moveZero(4, 7, 'd');
			moveZero(4, 5, 'l');
			moveZero(4, 1, 'u');

			break;
		case 5:
			moveZero(5, 4, 'l');
			moveZero(5, 8, 'd');
			moveZero(5, 2, 'u');

			break;
		case 6:
			moveZero(6, 7, 'r');
			moveZero(6, 3, 'u');
			break;
		case 7:
			moveZero(7, 8, 'r');
			moveZero(7, 4, 'u');
			moveZero(7, 6, 'l');

			break;
		case 8:
			moveZero(8, 7, 'l');
			moveZero(8, 5, 'u');
			break;
		}
		//printSpecific(*lastExpBranch);

		moveCounter++;
		if (SameBoard(openNodes.top(), goalState) || openNodes.empty())
		{
			cout << "Move counter: " << moveCounter << endl;
			cout << "Puzzle cleared!!" << endl;
			break;
		}
	}
}

void EightPuzzle::moveZero(int from, int to, char dir)
{
	Node tempNode;
	//Assigning value for lastExpBranch to the tempNode
	for (int i = 0; i < 9; i++)
	{
		tempNode.PuzzleState[i] = lastExpBranch->PuzzleState[i];
	}
	tempNode.g = lastExpBranch->g + 1;
	tempNode.h = WrongPositions(*lastExpBranch); //manhattan or WrongPosition
	tempNode.f_cost = tempNode.g + tempNode.h;

	//Setting the new position of the zero.
	tempNode.PuzzleState[from] = tempNode.PuzzleState[to];
	tempNode.PuzzleState[to] = 0;

	if (!isExpanded(tempNode))
	{
		openNodes.push(tempNode);
	}

}

int EightPuzzle::WrongPositions(Node puzzleNode)
{
	int wPos = 0;
	for (int i = 0; i < 9; i++)
	{
		if (puzzleNode.PuzzleState[i] != goalState.PuzzleState[i])
		{
			if (puzzleNode.PuzzleState[i] != 0)
			{
				wPos++;
			}
		}
	}

	return wPos;
}

bool EightPuzzle::SameBoard(Node puzzleNode, Node goalNode)
{
	for (int i = 0; i < 9; i++)
	{
		if (puzzleNode.PuzzleState[i] != goalNode.PuzzleState[i])
		{
			return false;
		}
	}

	return true;
}

bool EightPuzzle::isExpanded(Node puzzleNode)
{
	if (expTree.find(keyGen(puzzleNode)) == expTree.end())
	{
		return false;
	}
	else
	{
		return true;
	}
}

string EightPuzzle::keyGen(Node puzzleNode)
{
	string nodeLabel = "";

	for (int i = 0; i < 9; i++)
	{
		nodeLabel += to_string(puzzleNode.PuzzleState[i]);
		//cout << "nodeLabel: " << nodeLabel << endl;
	}

	return nodeLabel;
}

int EightPuzzle::findEmpty(Node puzzleNode)
{
	for (int i = 0; i < 9; i++)
	{
		if (puzzleNode.PuzzleState[i] == 0)
		{
			return i;
		}
	}
}

int EightPuzzle::manhattan(Node puzzleNode)
{
	int manhattanSum = 0;

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (puzzleNode.PuzzleState[i] == goalState.PuzzleState[j])
			{
				manhattanSum += manhattanDist(i, j);
				//cout << "ManhattanSum = " << manhattanSum << endl;
			}
		}
	}

	return manhattanSum;
}

int EightPuzzle::manhattanDist(int p1, int p2)
{
	int x1 = p1 % 3; // Vilken position på raden
	int y1 = p1 / 3; //Vilken rad

	int x2 = p2 % 3; // Vilken position på raden
	int y2 = p2 / 3; //Vilken rad

	return (abs(x1 - x2) + abs(y1 - y2));
}

void EightPuzzle::printSpecific(Node puzzleNode)
{
	cout << puzzleNode.PuzzleState[0] << " " << puzzleNode.PuzzleState[1] << " " << puzzleNode.PuzzleState[2] << endl <<
		puzzleNode.PuzzleState[3] << " " << puzzleNode.PuzzleState[4] << " " << puzzleNode.PuzzleState[5] << endl <<
		puzzleNode.PuzzleState[6] << " " << puzzleNode.PuzzleState[7] << " " << puzzleNode.PuzzleState[8] << endl <<
		"f: " << puzzleNode.f_cost << " and g: " << puzzleNode.g <<
		" and h: " << puzzleNode.h << endl << endl;
}

void EightPuzzle::print()
{
	cout << openNodes.top().PuzzleState[0] << " " << openNodes.top().PuzzleState[1] << " " << openNodes.top().PuzzleState[2] << endl <<
		openNodes.top().PuzzleState[3] << " " << openNodes.top().PuzzleState[4] << " " << openNodes.top().PuzzleState[5] << endl <<
		openNodes.top().PuzzleState[6] << " " << openNodes.top().PuzzleState[7] << " " << openNodes.top().PuzzleState[8] << endl <<
		"f: " << openNodes.top().f_cost << endl << "g: " << openNodes.top().g << endl <<
		"h: " << openNodes.top().h << endl;
}