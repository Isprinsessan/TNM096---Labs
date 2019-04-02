#include <vector>
#include <queue>
#include <map>

using namespace std;
struct Node
{
	int PuzzleState[9];
	int g; //g sum of actual costs from the start to the current node
	int h; //h estimated cost from the current node to the goal
	int f_cost; //f is the sum of g + h
};

struct NodeCompare
{
	bool operator()(const Node& ls, const Node& rs) const
	{
		return ls.f_cost > rs.f_cost;
	}
};

class EightPuzzle {
public:
	//constructor
	EightPuzzle();

	void PuzzleSolver();

	void print();
	//destructor
	//~EightPuzzle();


private:
	int manhattan(Node puzzleNode);
	int manhattanDist(int p1, int p2);

	int WrongPositions(Node puzzleNode);

	int findEmpty(Node puzzleNode);

	void moveZero(int from, int to, char dir);

	string keyGen(Node puzzleNode);

	bool isExpanded(Node puzzleNode);

	bool SameBoard(Node puzzleNode, Node goalNode);

	void printSpecific(Node puzzleNode);

	Node goalState;
	Node *lastExpBranch;

	map<string, Node> expTree;
	typedef priority_queue <Node, vector<Node>, NodeCompare> puzzlePQ;
	puzzlePQ openNodes;
};