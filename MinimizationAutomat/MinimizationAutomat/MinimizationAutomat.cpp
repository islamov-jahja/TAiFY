// MinimizationAutomat.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "functions_for_minimization.h"

int main()
{
	ifstream inFile("in1.txt");
	ofstream outFile("output.txt");

	size_t stateForm;
	inFile >> stateForm;
	size_t countOfOutputState;
	size_t countOfInputState;
	size_t countOfState;

	inFile >> countOfInputState;
	inFile >> countOfOutputState;
	inFile >> countOfState;
	if (stateForm == MILI)
		vector<vector<TransitionAndOutputState>> ArrWithMinimizedMili = GetArrWithMinimizedMili(outFile, inFile, countOfInputState, countOfOutputState, countOfState, stateForm);
	else
		vector<vector<TransitionAndOutputState>> ArrWithMinimizedMili = GetArrWithMinimizedMur(outFile, inFile, countOfInputState, countOfOutputState, countOfState, stateForm);
   
	return 0;
}

