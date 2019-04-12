#pragma once
#include <string>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <ctime>

using namespace std;

class State
{
public:
	
	string schedule[24] = { "MT101", "MT102", "MT103", "MT104", "MT105", "MT106", "MT107",
							"MT201", "MT202", "MT203", "MT204", "MT205", "MT206",
							"MT301", "MT302", "MT303", "MT304",
							"MT401", "MT402", "MT403",
							"MT501", "MT502", "     ", "     " };

	int numberOfConflicts;
	int score = 0;

	State();

	void Solve();
	
	int GetNumberOfConflicts();

	int FindMinConflicts(int _indx);

	int FindConflicts(string _compare, int _indx);

	void SwapIndexPosition(int _indx1, int _indx2);

	void PreferenceScore();

	void print();
};

