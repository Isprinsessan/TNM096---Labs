// Lab1.cpp : Implementing an A* algorithm to solve the 8-puzzle problem
// ******************************
// Author: Erik Nilsson
// Course: TNM096: Artificial intelligence, principles and techniques, Linköpings university
// Date: 26 March 2019
// ******************************

#include "stdafx.h"
#include "Puzzle.h"
#include <iostream>

using namespace std;

int main()
{
	Puzzle P;

	cout << "Starting: " << endl;
	cout << "Starting puzzle: " << endl;
	P.print();
	P.MoveEmpty();

	cout << "" << endl;
	cout << "Done " << endl;
	cout << "Final matrix: " << endl;
	P.print();

	int a;
	cin >> a;

    return 0;
}

