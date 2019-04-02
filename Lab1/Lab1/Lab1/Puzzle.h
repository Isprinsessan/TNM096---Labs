#include "stdafx.h"
#include <vector>
#include <queue>
#include <string>
#include <map>
#include <iostream>

struct Node {
	int puzzleState[9];
	int g;
	int h;
	int f;
};

struct CompareNode {

	bool operator()(const Node& lhs, const Node& rhs) {
		return lhs.f > rhs.f;
	}

};

class Puzzle
{

public:

	Puzzle();

	void MoveEmpty();

	void print();

private:

	void MoveTile(int _start, int _end);

	int ManhattanSum(Node _node);

	int ManhattanDistance(int _start, int _end);

	int GetHCost(Node _node);

	int FindEmpty(Node _node);

	bool ComparePuzzles(Node _node1, Node _node2);

	bool NodeInSet(Node _node);

	std::string createKey(Node _node);

	Node goalState;
	Node* latestNode;

	std::map<std::string, Node> closedSet;

	typedef std::priority_queue<Node, std::vector<Node>, CompareNode> PQ;
	PQ openSet;
};

