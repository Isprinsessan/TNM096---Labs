#include "stdafx.h"
#include <iostream>
#include <algorithm>
using namespace std;
#include "Puzzle.h"
#include <stdlib.h>

struct less_than_key
{
	inline bool operator() (const PuzzleNode& struct1, const PuzzleNode& struct2)
	{
		return (struct1.cost > struct2.cost);
	}
};


int Puzzle::CostCalc(PuzzleNode n) {

	//int cost = MisplacedTiles(n);
	int cost = ManhattanCalc(n);
	// cout << endl << "Man: " << cost << endl << " mis: " << MisplacedTiles(n);
	return cost;
}

Puzzle::Puzzle() {
	//row 1
	data.puzzleState[0] = 1;
	data.puzzleState[1] = 0;
	data.puzzleState[2] = 5;
	//row 2
	data.puzzleState[3] = 6;
	data.puzzleState[4] = 4;
	data.puzzleState[5] = 7;
	//row 3
	data.puzzleState[6] = 2;
	data.puzzleState[7] = 3;
	data.puzzleState[8] = 8;
	//stegen man gått
	data.g = 0;
	//hur många rutor som är fel
	data.h = CostCalc(data);
	//f, h +g
	data.cost = data.h + data.g;

	//openNodes.push_back(data);



	openNodes.push(data);
	bestPath.cost = -1;
}

void Puzzle::SolvePuzzle() {
	int counter = 0;
	PuzzleNode temp;
	while (true) {//openNodes.size() > 0) {

				  // std::sort(openNodes.begin(), openNodes.end(), less_than_key());
		temp = openNodes.top();
		openNodes.pop();
		closedNodes.push_back(temp);
		//cout <<"size: " << openNodes.size()<< endl;
		//print(temp);






		if (MisplacedTiles(temp) == 0) {
			if (bestPath.cost == -1 || temp.cost < bestPath.cost) {
				bestPath = temp;
				cout << "counter: " << counter;
				cout << endl << "-----DONE-----" << endl;
				print(bestPath);
				break;
			}
		}
		else {
			MovePuzzle(temp);
		}
		counter++;

	}
}



int Puzzle::GetEmptyPos(PuzzleNode n) {
	int temp = 0;
	for (int i = 0; i<9; i++) {
		if (n.puzzleState[i] == 0) {
			temp = i;
		}
	}
	return temp;
}

void Puzzle::MovePuzzle(PuzzleNode n) {

	switch (GetEmptyPos(n)) {
	case 0:
		//right
		MakeEmptyMove(0, 1, n);
		//down
		MakeEmptyMove(0, 3, n);
		break;
	case 1:
		//left
		MakeEmptyMove(1, 0, n);
		//right
		MakeEmptyMove(1, 2, n);
		//down
		MakeEmptyMove(1, 4, n);

		break;
	case 2:
		//left
		MakeEmptyMove(2, 1, n);
		//down
		MakeEmptyMove(2, 5, n);
		break;
	case 3:
		//up
		MakeEmptyMove(3, 0, n);
		//right
		MakeEmptyMove(3, 4, n);
		//down
		MakeEmptyMove(3, 6, n);
		break;
	case 4:
		//up
		MakeEmptyMove(4, 1, n);
		//left
		MakeEmptyMove(4, 3, n);
		//right
		MakeEmptyMove(4, 5, n);
		//down
		MakeEmptyMove(4, 7, n);

		break;
	case 5:
		//up
		MakeEmptyMove(5, 2, n);
		//left
		MakeEmptyMove(5, 4, n);
		//down
		MakeEmptyMove(5, 8, n);
		break;
	case 6:
		//up
		MakeEmptyMove(6, 3, n);
		//right
		MakeEmptyMove(6, 7, n);
		break;
	case 7:
		//up
		MakeEmptyMove(7, 4, n);
		//left
		MakeEmptyMove(7, 6, n);
		//right
		MakeEmptyMove(7, 8, n);
		break;
	case 8:
		//up
		MakeEmptyMove(8, 5, n);
		//left
		MakeEmptyMove(8, 7, n);
		break;
	default:
		break;
	}


}

void Puzzle::MakeEmptyMove(int start, int move, PuzzleNode n) {
	PuzzleNode temp;

	for (int i = 0; i<9; i++) {
		temp.puzzleState[i] = n.puzzleState[i];
	}
	int score_g = n.g;

	temp.g = score_g + 1;
	temp.h = CostCalc(temp);
	temp.cost = temp.g + temp.h;


	temp.puzzleState[start] = temp.puzzleState[move];
	temp.puzzleState[move] = 0;


	if (!checkIfClosed(temp)) {

		openNodes.push(temp);


	}



}
bool Puzzle::checkIfClosed(PuzzleNode n) {
	PuzzleNode temp;
	for (int i = 0; i < closedNodes.size(); i++) {
		temp = closedNodes[i];
		if (comparePuzzleNode(n, temp)) {
			return true;
		}
	}

	return false;
}
bool Puzzle::comparePuzzleNode(PuzzleNode n, PuzzleNode p) {

	//bool equal = true;

	for (int i = 0; i < 9; i++) {
		if (n.puzzleState[i] != p.puzzleState[i]) {

			return false;
		}
	}


	return true;

}
int Puzzle::ManhattanCalc(PuzzleNode n) {
	int sum = 0;

	for (int i = 0; i<9; i++) {
		if (n.puzzleState[i] != 0) {
			sum += ManhattanDist((n.puzzleState[i] - 1), i);
		}
	}
	return sum;

}
int Puzzle::ManhattanDist(int p1, int p2) {

	int x_val = p1 % 3;
	int y_val = p1 / 3;
	int x_goal = p2 % 3;
	int y_goal = p2 / 3;

	return abs(x_val - x_goal) + abs(y_val - y_goal);
}
int Puzzle::MisplacedTiles(PuzzleNode n) {
	int count = 0;
	for (int i = 0; i <9; i++) {
		if ((n.puzzleState[i] != (i + 1)) && (n.puzzleState[i] != 0)) {

			count++;
		}
	}
	return count;
}

void Puzzle::print(PuzzleNode n) {
	cout << "\n" << n.puzzleState[0] << " " << n.puzzleState[1] << " " << n.puzzleState[2] << "\n" << n.puzzleState[3] << " " << n.puzzleState[4] << " " << n.puzzleState[5] << "\n" <<
		n.puzzleState[6] << " " << n.puzzleState[7] << " " << n.puzzleState[8] << "\n";
	cout << "cost: " << n.cost << "\n" << "steg: " << n.g << endl;
}