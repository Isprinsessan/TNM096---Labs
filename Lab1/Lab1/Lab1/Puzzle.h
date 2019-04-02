#include "stdafx.h"
#define Puzzle_h
#include <vector>
#include <queue>

struct PuzzleNode {
	int puzzleState[9];
	int g;
	int h;
	int cost;

};
struct quecompare
{
	bool operator()(const PuzzleNode& lhs, const PuzzleNode& rhs) const
	{
		return lhs.cost > rhs.cost;
	}
};


class Puzzle
{
public:
	Puzzle();
	void print(PuzzleNode n);

	void SolvePuzzle();
	int MisplacedTiles(PuzzleNode n);
	int GetEmptyPos(PuzzleNode n);
	void MakeEmptyMove(int start, int move, PuzzleNode n);
	void MovePuzzle(PuzzleNode n);
	bool comparePuzzleNode(PuzzleNode n, PuzzleNode p);
	bool checkIfClosed(PuzzleNode n);
	int CostCalc(PuzzleNode n);
	int ManhattanDist(int p1, int p2);
	int ManhattanCalc(PuzzleNode n);
	//std::vector<PuzzleNode> openNodes;
	std::vector<PuzzleNode> closedNodes;

	//std::priority_queue<PuzzleNode, std::vector<PuzzleNode>, std::less<int>> openNodes;
	typedef std::priority_queue<PuzzleNode, std::vector<PuzzleNode>, quecompare> priorityQue;
	priorityQue openNodes;
	PuzzleNode data;
private:

	PuzzleNode bestPath;
	//Puzzle* next;



};
