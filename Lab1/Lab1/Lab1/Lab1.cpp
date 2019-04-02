//// Lab1.cpp : Defines the entry point for the console application.
////
//
#include "stdafx.h"
#include <iostream>
//#include <stack>
//#include <vector>
//#include <algorithm>
//#include <map>
//#include <set>
//#include <queue>
#include "Puzzle.h"
#include "Node.h"

using namespace std;

//struct Node
//{
//	int puzzleState[9];
//	int g;
//	int h;
//	int Fcost;
//	Node *previous;
//
//	Node& operator=(Node n)
//	{
//		for (int i = 0; i < 9; i++)
//		{
//			std::swap(puzzleState[i], n.puzzleState[i]);
//		}
//		std::swap(g, n.g);
//		std::swap(h, n.h);
//		std::swap(Fcost, n.Fcost);
//		std::swap(previous, n.previous);
//		return *this;
//	}
//
//	bool operator==(const Node &n) const
//	{
//		bool sant = true;
//		for (int i = 0; i < 9; i++)
//		{
//			if (n.puzzleState[i] != puzzleState[i])
//				sant = false;
//		}
//		if (n.g != g || n.h != h || n.Fcost != Fcost || sant == false)
//			return false;
//		else
//			return true;
//	}
//};
//
//struct NodeCompare
//{
//	bool operator()(const Node& lhs, const Node& rhs) const
//	{
//		return lhs.Fcost > rhs.Fcost;
//	}
//};
//
//typedef priority_queue <Node, std::vector<Node>, NodeCompare> puzzlePQ;
//
//bool ComparePuzzles(Node a, Node b);
//
//void AStarSearch();
//
//int GetHcost(Node a);
//
//int ManhattanDistance(Node n);
//
//int CalculateManhattanDistance(int StartPosition, int GoalPosition);
//
//int FindEmpty(Node puzzle);
//
//bool NodeExists(std::vector<Node> NodeList, Node n);
//
//bool NodeExistCompare(Node p1, Node p2);
//
//std::vector<Node> GetNeighbours(int empty, Node currentNode, puzzlePQ &openSet, std::vector<Node> closedSet);
//
//Node moveEmpty(int startPosition, int movedPosition, Node currentNode, puzzlePQ &openSet, std::vector<Node> closedSet);
//
//void print(Node finalPuzzle, int nrOfSteps);

int main()
{
	//**************

	EightPuzzle thePuzzle;
	thePuzzle.PuzzleSolver();
	thePuzzle.print();

	//*******************
	//Puzzle puzzle;

	//// puzzle.print(puzzle.openNodes.top());
	//puzzle.print(puzzle.data);
	//puzzle.SolvePuzzle();
	//*******************
	//AStarSearch();

	int a;
	std::cin >> a;
    return 0;
}

//bool ComparePuzzles(Node a, Node b)
//{
//	for (int i = 0; i < 9; i++)
//	{
//		if (a.puzzleState[i] != b.puzzleState[i])
//			return false;
//	}
//
//	return true;
//}
//
//int FindEmpty(Node puzzle)
//{
//	for (int i = 0; i < 9; i++)
//		if (puzzle.puzzleState[i] == 0)
//			return i;
//
//	return 0;
//}
//
//int GetHcost(Node a)
//{
//	int Goal[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 0 };
//	int h = 0;
//	
//	for (int i = 0; i < 9; i++)
//	{
//		if (a.puzzleState[i] != Goal[i])
//			h++;
//	}
//
//	return h;
//}
//
//int ManhattanDistance(Node n)
//{
//	int sum = 0;
//	for (int i = 0; i < 9; i++)
//	{
//		int TileValue = n.puzzleState[i];
//		int GoalPosition = TileValue - 1;
//
//		if (TileValue == 0)
//			continue;
//
//		sum += CalculateManhattanDistance(i, GoalPosition);
//	}
//
//	return sum;
//}
//
//int CalculateManhattanDistance(int StartPosition,int GoalPosition)
//{
//	int x1 = StartPosition % 3;	//Kolumn
//	int y1 = StartPosition / 3;	//Rad
//
//	int x2 = GoalPosition % 3; 
//	int y2 = GoalPosition / 3;
//
//	return (abs(x1 - x2) + abs(y1 - y2));
//}
//
//std::vector<Node> GetNeighbours(int empty, Node current, puzzlePQ &openSet, std::vector<Node> closedSet)
//{
//	std::vector<Node> Nodes;
//
//	switch (empty)
//	{
//	case 0:
//		// Empty is in top left
//		Nodes.push_back(moveEmpty(empty, 1, current, openSet, closedSet));	//Move left
//		Nodes.push_back(moveEmpty(empty, 3, current, openSet, closedSet));	//Move down
//		break;
//	case 1:
//		// Empty is in top middle
//		Nodes.push_back(moveEmpty(empty, 0, current, openSet, closedSet));	//Move left
//		Nodes.push_back(moveEmpty(empty, 2, current, openSet, closedSet));	//Move right
//		Nodes.push_back(moveEmpty(empty, 4, current, openSet, closedSet));	//Move down
//		break;
//	case 2:
//		// Empty is in top right
//		Nodes.push_back(moveEmpty(empty, 1, current, openSet, closedSet));	//Move left
//		Nodes.push_back(moveEmpty(empty, 5, current, openSet, closedSet));	//Move down
//		break;
//	case 3:
//		// Empty is in middle left
//		Nodes.push_back(moveEmpty(empty, 0, current, openSet, closedSet));	//Move up
//		Nodes.push_back(moveEmpty(empty, 4, current, openSet, closedSet));	//Move right
//		Nodes.push_back(moveEmpty(empty, 6, current, openSet, closedSet));	//Move down
//		break;
//	case 4:
//		// Empty is in middle middle
//		Nodes.push_back(moveEmpty(empty, 1, current, openSet, closedSet));	//Move up
//		Nodes.push_back(moveEmpty(empty, 3, current, openSet, closedSet));	//Move left
//		Nodes.push_back(moveEmpty(empty, 5, current, openSet, closedSet));	//Move right
//		Nodes.push_back(moveEmpty(empty, 7, current, openSet, closedSet));	//Move down
//		break;
//	case 5:
//		// Empty is in middle left
//		Nodes.push_back(moveEmpty(empty, 2, current, openSet, closedSet));	//Move up
//		Nodes.push_back(moveEmpty(empty, 4, current, openSet, closedSet));	//Move left
//		Nodes.push_back(moveEmpty(empty, 8, current, openSet, closedSet));	//Move down
//		break;
//	case 6:
//		// Empty is in bottom left
//		Nodes.push_back(moveEmpty(empty, 3, current, openSet, closedSet));	//Move up
//		Nodes.push_back(moveEmpty(empty, 7, current, openSet, closedSet));	//Move right
//		break;
//	case 7:
//		// Empty is in bottom middle
//		Nodes.push_back(moveEmpty(empty, 4, current, openSet, closedSet));	//Move up
//		Nodes.push_back(moveEmpty(empty, 6, current, openSet, closedSet));	//Move left
//		Nodes.push_back(moveEmpty(empty, 8, current, openSet, closedSet));	//Move right
//		break;
//	case 8:
//		// Empty is in bottom right
//		Nodes.push_back(moveEmpty(empty, 5, current, openSet, closedSet));	//Move up
//		Nodes.push_back(moveEmpty(empty, 7, current, openSet, closedSet));	//Move left
//		break;
//	}
//
//	return Nodes;
//}
//
//Node moveEmpty(int _start, int _moved, Node current, puzzlePQ &openSet, std::vector<Node> closedSet)
//{
//	Node temp;
//	for (int i = 0; i < 9; i++)
//	{
//			temp.puzzleState[i] = current.puzzleState[i];
//	}
//	temp.g = current.g + 1;
//
//	//temp.h = GetHcost(current);
//	temp.h = ManhattanDistance(current);
//	//Move the square
//	temp.Fcost = temp.g + temp.h;
//	temp.puzzleState[_start] = temp.puzzleState[_moved];
//	temp.puzzleState[_moved] = 0;
//
//	//If the node is already in the closed set
//	if (!NodeExists(closedSet, temp))
//	{
//		openSet.push(temp);
//	}
//
//	return temp;
//
//}
//
//bool NodeExists(std::vector<Node> NodeList, Node n)
//{
//	Node temp;
//	for (int i = 0; i < NodeList.size(); i++)
//	{
//		temp = NodeList[i];
//
//		if (NodeExistCompare(n, temp))
//			return true;
//	}
//
//	return false;
//}
//
//bool NodeExistCompare(Node p1, Node p2)
//{
//	for (int j = 0; j < 9; j++)
//	{
//		if (p1.puzzleState[j] != p2.puzzleState[j])
//			return false;
//	}
//	return true;
//}
//
//void AStarSearch()
//{
//	//Create the two nodes containing the start and goal puzzles
//	Node startPuzzle;
//	Node goalPuzzle;
//
//	Node finalPuzzle;
//	int nrOfSteps = 0;
//	//Create the starting puzzle
//	startPuzzle.puzzleState[0] = 1; startPuzzle.puzzleState[1] = 0; startPuzzle.puzzleState[2] = 5;
//	startPuzzle.puzzleState[3] = 6; startPuzzle.puzzleState[4] = 4; startPuzzle.puzzleState[5] = 7;
//	startPuzzle.puzzleState[6] = 2; startPuzzle.puzzleState[7] = 3; startPuzzle.puzzleState[8] = 8;
//
//	//startPuzzle.puzzleState[0] = 4; startPuzzle.puzzleState[1] = 1; startPuzzle.puzzleState[2] = 2;
//	//startPuzzle.puzzleState[3] = 5; startPuzzle.puzzleState[4] = 8; startPuzzle.puzzleState[5] = 3;
//	//startPuzzle.puzzleState[6] = 0; startPuzzle.puzzleState[7] = 7; startPuzzle.puzzleState[8] = 6;
//
//	//startPuzzle.puzzleState[0] = 1; startPuzzle.puzzleState[1] = 0; startPuzzle.puzzleState[2] = 3;
//	//startPuzzle.puzzleState[3] = 4; startPuzzle.puzzleState[4] = 2; startPuzzle.puzzleState[5] = 6;
//	//startPuzzle.puzzleState[6] = 7; startPuzzle.puzzleState[7] = 5; startPuzzle.puzzleState[8] = 8;
//
//	std::cout << "Starting matrix" << std::endl;
//	std::cout << startPuzzle.puzzleState[0] << "  " << startPuzzle.puzzleState[1] << "  " << startPuzzle.puzzleState[2] << std::endl;
//	std::cout << startPuzzle.puzzleState[3] << "  " << startPuzzle.puzzleState[4] << "  " << startPuzzle.puzzleState[5] << std::endl;
//	std::cout << startPuzzle.puzzleState[6] << "  " << startPuzzle.puzzleState[7] << "  " << startPuzzle.puzzleState[8] << std::endl;
//
//	//Create the goal puzzle
//	goalPuzzle.puzzleState[0] = 1; goalPuzzle.puzzleState[1] = 2; goalPuzzle.puzzleState[2] = 3;
//	goalPuzzle.puzzleState[3] = 4; goalPuzzle.puzzleState[4] = 5; goalPuzzle.puzzleState[5] = 6;
//	goalPuzzle.puzzleState[6] = 7; goalPuzzle.puzzleState[7] = 8; goalPuzzle.puzzleState[8] = 0;
//
//	//Set the variables for the starting puzzle
//	startPuzzle.g = 0;
//	//startPuzzle.h = GetHcost(startPuzzle);
//	startPuzzle.h = ManhattanDistance(startPuzzle);
//	startPuzzle.Fcost = startPuzzle.g + startPuzzle.h;
//
//	//Vectors to contain the nodes
//	std::vector<Node> closedSet;
//	//std::vector<Node> openSet;
//
//	puzzlePQ openSet;
//
//	//Add the empty node of the first puzzle to the stack
//	openSet.push(startPuzzle);
//
//	//Bool to check if the goal puzzle has been found
//	bool status = false;
//	int counter = 0;
//
//	while (!openSet.empty())
//	{
//		//Find the node with the lowest f-cost
//		Node current = openSet.top();
//
//		if (ComparePuzzles(current, goalPuzzle))
//		{
//			finalPuzzle = current;
//			nrOfSteps = current.g;
//			status = true;
//			break;
//		}
//		
//		//Remove the node from the queue
//		openSet.pop();
//
//		//Add the node to the tagged set
//		closedSet.push_back(current);
//
//		//Find the neighbours of the empty node in the current set
//		std::vector<Node> neighbourNodes = GetNeighbours(FindEmpty(current), current, openSet, closedSet);
//
//		//print(current, counter);
//
//	}
//	std::cout << "Done" << std::endl;
//	//If the puzzle has been found, display it
//	if (status)
//		print(finalPuzzle, nrOfSteps);
//	else
//		std::cout << "No solution found" << std::endl;
//
//
//}
//
//
//void print(Node finalPuzzle, int nrOfSteps)
//{
//	std::cout << "" << std::endl;
//	std::cout << "New matrix" << std::endl;
//	std::cout << finalPuzzle.puzzleState[0] << "  " << finalPuzzle.puzzleState[1] << "  " << finalPuzzle.puzzleState[2] << std::endl;
//	std::cout << finalPuzzle.puzzleState[3] << "  " << finalPuzzle.puzzleState[4] << "  " << finalPuzzle.puzzleState[5] << std::endl;
//	std::cout << finalPuzzle.puzzleState[6] << "  " << finalPuzzle.puzzleState[7] << "  " << finalPuzzle.puzzleState[8] << std::endl;
//	std::cout << "" << std::endl;
//	std::cout << "f: " << finalPuzzle.Fcost << " g: " << finalPuzzle.g << " h: " << finalPuzzle.h << std::endl;
//	std::cout << "Done in " << nrOfSteps << " number of steps." << std::endl;
//
//}
//
//
