#include "stdafx.h"
#include "State.h"

using namespace std;

State::State()
{
	//Create a random schedule and calculate the number of conflicts in it
	//srand(time(0));
	std::random_shuffle(std::begin(schedule), std::end(schedule));
	numberOfConflicts = GetNumberOfConflicts();

}

void State::Solve()
{	 
	int totNrOfConflicts = numberOfConflicts;

	int nrOfIt = 0;
	int maxIt = 10000;

	//While not doing too many iterations and while there still are conflicts
	while (nrOfIt < maxIt && totNrOfConflicts > 0)
	{
		nrOfIt++;

		double random = (double)rand() / (double)RAND_MAX;

		//Get a random course index from the schedule
		int index = (int)( (size(schedule) -1 )* random);

		//Get the slot in the schedule with the lowest amount of conflicts
		int minIndex = FindMinConflicts(index);

		//cout << "index " << index <<  "  minIndex " << minIndex<< endl;

		//Swap the courses position in the schedule
		SwapIndexPosition(index, minIndex);

		//Update the total number of conflicts in the schedule
		totNrOfConflicts = GetNumberOfConflicts();
	}

	//Print out if no solution was found
	if (nrOfIt == maxIt)
	{
		cout << "" << endl; 
		cout << "No solution found in " << nrOfIt << " iterations" << endl;
	}

	//Set the schedules number of conflicts
	numberOfConflicts = totNrOfConflicts;

	/*cout << endl;
	cout << "Number of iterations: " << nrOfIt << endl;
	cout << endl;
*/

	//Task 4
	PreferenceScore();

}

int State::GetNumberOfConflicts()
{
	int conflicts = 0;

	for (int i = 0; i < std::size(schedule); i+=3)
	{
		//Get course code infromation for each column
		string Col1 = schedule[i];
		string Col2 = schedule[i + 1];
		string Col3 = schedule[i + 2];

		//cout << Col1[2] << "    " << Col2[2] << "   " << Col3[2] << endl;

		//Compare the course numbers, increase conflict if they are the same (Col1[2] gives a char))
		if (Col1[2] == Col2[2])
			conflicts++;
		if (Col1[2] == Col3[2])
			conflicts++;
		if (Col2[2] == Col3[2])
			conflicts++;
	}

	return conflicts;
}

int State::FindMinConflicts(int _indx)
{
	//Get the current course being evaluated and its fist course digit
	string CurrentEvaluation = schedule[_indx];
	string courseDigits(1, CurrentEvaluation[2]);

	int minIndex = _indx;
	int minIndexConflicts = 9999;
	
	//Special case for when there is an empty string in the course list
	if (courseDigits.compare(" ") == 0)
		return _indx;

	//Compare CurrentEvaluation to all other slots in the schedule
	for (int i = 0; i < std::size(schedule); i++)
	{
		//For each slot in the schedule, find the number of conflicts if the current course is moved there
		int nrOfConflicts = FindConflicts(courseDigits, i);

		if (nrOfConflicts < minIndexConflicts)
		{
			//String to check if the current slot have the same course digit as the moved one
			string compare(1, schedule[i][2]);

			//If they are not the same, set it to the lowest
			if (compare != courseDigits)
			{
				//Set min index to the current slot and update the amount of min conflicts
				minIndexConflicts = nrOfConflicts;
				minIndex = i;
			}

		}
	}

	return minIndex;
}

int State::FindConflicts(string _compare, int _indx)
{
	//Get the current column
	int col = _indx % 3;
	int conflicts = 0;

	string neighbour1 = "";
	string neighbour2 = "";

	//Special case for MT5**
	if (_compare.compare("5") == 0)
		return 0;

	//Get neighbours from the column
	switch (col)
	{
	case 0:
		//indx is in the left column
		neighbour1 = schedule[_indx + 1];
		neighbour2 = schedule[_indx + 2];
		break;
	case 1:
		//indx is in the middle column
		neighbour1 = schedule[_indx - 1];
		neighbour2 = schedule[_indx + 1];
		break;
	case 2:
		//indx is in the right column
		neighbour1 = schedule[_indx - 1];
		neighbour2 = schedule[_indx - 2];
		break;
	}

	//Get the first course digit
	string neigh1(1, neighbour1[2]);
	string neigh2(1, neighbour2[2]);

	//If any of the neighbours course digit is the same as the current one, increase conflict
	if (_compare.compare(neigh1) == 0)
		conflicts++;
	if (_compare.compare(neigh2) == 0)
		conflicts++;

	return conflicts;
	
}

void State::SwapIndexPosition(int _indx1, int _indx2)
{
	//Swap the courses position in the schedule
	string temp = schedule[_indx1];
	schedule[_indx1] = schedule[_indx2];
	schedule[_indx2] = temp;
}

void State::PreferenceScore()
{
	int row0 = 0 * 3;
	int row3 = 3 * 3;
	int row4 = 4 * 3;
	int row5 = 5 * 3;
	int row7 = 7 * 3;

	//Loop through row0 (09:00)
	for (int i = row0; i < row0 + 3; i++)
	{
		string temp0(1, schedule[i][2]);
		//cout << "temp0  " << temp0 << endl;
		if (temp0.compare(" ") == 0)
		{
			//cout <<  "temp = 0  " << temp0 << endl;
			score++;
		}
	}

	//Loop through row3 (12:00)
	for (int i = row3; i < row3 + 3; i++)
	{
		string temp3(1, schedule[i][2]);
		//cout << temp3 << endl;
		if (temp3.compare(" ") == 0)
		{
			//cout << "temp = 0  " << temp3 << endl;
			score++;
		}
	}

	//Loop through row7 (16:00)
	for (int i = row7; i < row7 + 3; i++)
	{
		string temp7(1, schedule[i][2]);
		//cout << temp7 << endl;
		if (temp7.compare(" ") == 0)
		{
			//cout << "temp = 0  " << temp7 << endl;
			score++;
		}
	}

	//Check if MT501 or MT502 is scheduled at 1 or 2
	//For 13:00
	for (int i = row4; i < row4 + 3; i++)
	{
		string temp4(1, schedule[i][2]);
		if (temp4.compare("5") == 0)
		{
			//cout << "temp = 5  " << temp4 << endl;
			score++;
		}
	}

	//For 14:00
	for (int i = row5; i < row5 + 3; i++)
	{
		string temp5(1, schedule[i][2]);
		if (temp5.compare("5") == 0)
		{
			score++;
		}
	}


}

void State::print() {
	cout << "TP51     " << "SP34     " << "K3       " << endl;
	cout << "----     " << "----     " << "----     " << endl;
	for (int row = 0; row < 8; row++)
	{
		for (int col = 0; col < 3; col++)
		{
			cout << schedule[row * 3 + col] << "    ";
		}
		cout << "  " << row + 9 << endl;
		
	}
	cout << endl;
	cout << "Number of conflicts: " << numberOfConflicts << endl;
	cout << endl;
}
