// Lab2.cpp : Create a non conflicting course schedule by implementing a Min-Conflic algorithm
// ******************************
// Author: Erik Nilsson
// Course: TNM096: Artificial intelligence, principles and techniques, Linköpings university
// Date: 4 april 2019
// ******************************

#include "stdafx.h"
#include "State.h"
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	srand(time(0));
	//Task 3
	//State Schedule;

	//cout << "Starting schedule: " << endl;
	//Schedule.print();
	//Schedule.Solve();

	//cout << "Final schedule: " << endl;
	//Schedule.print();

	//Task 4
	vector<State> Schedules;
	
	int maxScore = 0;
	int bestIndex = 0;

	int iterations = 0;
	while (iterations < 500)
	{
		cout << iterations << endl;
		State schedule;
		//schedule.print();
		schedule.Solve();
		//cout << "score " << schedule.score << endl;
		if (schedule.numberOfConflicts != 0)
			continue;

		Schedules.push_back(schedule);
		iterations++;

		if (schedule.score > maxScore)
		{
			maxScore = schedule.score;
			bestIndex = iterations;
		}

		if (schedule.score == 4)
			break;
	}
	cout << "size of schedules:  " << Schedules.size() << endl;
	cout << "best index " << bestIndex << endl;
	cout << "best score " << maxScore << endl;
	cout << "Best schedule: " << endl;
	Schedules.at(bestIndex-1).print();
	cout << "Number of fullfilled preferences: " << Schedules[bestIndex-1].score << endl;


	int a;
	cin >> a;
	
    return 0;
}

