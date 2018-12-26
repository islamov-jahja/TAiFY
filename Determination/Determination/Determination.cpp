// Determination.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
struct State {
	vector<int> state;
	bool isFinalState = false;
};

const int NotState = -1;

void ReadFinalStates(vector<int>& finalStates, int countOfFinalStates, ifstream& inFile);
void ReadStartStateOfAutomat(vector<vector<State>>& startStateOfAutomat, int countOfState, ifstream& inFile, vector<int> finalStates, int countOfInputStates);
void ShowAutomat(vector<vector<State>>& startStateOfAutomat, int countOfStates, int countOfInputStates);
vector<vector<State>> GetDeterminateAutomat(vector<vector<State>> startStateOfAutomat, int countOfStates, int countOfInputStates);
void AddStartStateToDeterminationAutomat(vector<vector<State>>& determinationAutomat, vector<vector<State>> startStateOfAutomat, int countOfInputStates);
void AddNewStateToDeterminationAutomat(vector<vector<State>>& determinationAutomat, vector<vector<State>> startAutomat, int countOfInputStates, State state);
int GetIndexIfStateFoundInAutomat(vector<vector<State>> determinationAutomat, State stateForCheck);
void InitializeFinalStatesInDeterminateAutomat(vector<vector<State>>& determinationAutomat, vector<int> finalStates, vector<int>& newFinalStates);
void PrintAutomat(vector<vector<State>> determinateAutomat, ofstream& outFile, vector<int> finalStates, int countOfInputStates);
void DrawAutomat(vector<vector<State>> determinationAutomat, int countOfInputStates, string fileName);

int main(int argc, char* argv[])
{
	if (argc < 3) {
		cout << "error - few arguments" << endl;
		return 1;
	}

	string fileName = argv[3];
	ifstream inFile(argv[1]);
	ofstream outFile(argv[2]);

	int countOfInputStates;
	int countOfStates;
	int countOfFinalStates;

	inFile >> countOfInputStates >> countOfStates >> countOfFinalStates;
	vector<int> finalStates(countOfFinalStates, 0);
	vector<vector<State>> startStateOfAutomat(countOfStates, vector<State>(countOfInputStates + 1));
	vector<int> newFinalStates;

	ReadFinalStates(finalStates, countOfFinalStates, inFile);
	ReadStartStateOfAutomat(startStateOfAutomat, countOfStates, inFile, finalStates, countOfInputStates);
	vector<vector<State>> determinationAutomat = GetDeterminateAutomat(startStateOfAutomat, countOfStates, countOfInputStates);
	InitializeFinalStatesInDeterminateAutomat(determinationAutomat, finalStates, newFinalStates);
	PrintAutomat(determinationAutomat, outFile, newFinalStates, countOfInputStates);
	DrawAutomat(determinationAutomat, countOfInputStates, fileName);

    return 0;
}

void DrawAutomat(vector<vector<State>> determinationAutomat, int countOfInputStates, string fileName)
{
	ofstream dotFile(fileName);
	dotFile << "digraph DeterminatedStateMachine {" << std::endl;
	for (size_t i = 0; i < determinationAutomat.size(); i++)
	{
		if (determinationAutomat[i][0].isFinalState)
		{
			dotFile << i << " [shape = box]" << endl;
		}
		else
		{
			dotFile << i << endl;
		}
	}

	for (size_t i = 0; i < determinationAutomat.size(); i++)
	{
		for (size_t j = 1; j <= countOfInputStates; j++)
		{
			if (determinationAutomat[i][j].state[0] != -1)
			{
				dotFile << "	" << i << "->" << GetIndexIfStateFoundInAutomat(determinationAutomat, determinationAutomat[i][j]) << "[label=" << j-1 << ']' << endl;
			}
		}
	}

	dotFile << "}";
	dotFile.close();
}

void PrintAutomat(vector<vector<State>> determinateAutomat, ofstream& outFile, vector<int> finalStates, int countOfInputStates)
{
	outFile << countOfInputStates << endl;
	outFile << determinateAutomat.size() << endl;
	outFile << finalStates.size() << endl;
	for (size_t i = 0; i < finalStates.size(); i++)
		outFile << finalStates[i] << ' ';

	outFile << endl;
	
	for (size_t i = 0; i < determinateAutomat.size(); i++)
	{
		for (size_t j = 1; j <= countOfInputStates; j++)
		{
			outFile << GetIndexIfStateFoundInAutomat(determinateAutomat, determinateAutomat[i][j])  << ' ' << j - 1 << ' ';
		}
		outFile << endl;
	}
}

void InitializeFinalStatesInDeterminateAutomat(vector<vector<State>>& determinationAutomat, vector<int> finalStates, vector<int>& newFinalStates)
{
	bool finalStateFind = false;
	for(size_t i = 0; i < determinationAutomat.size(); i++)
		for (size_t j = 0; j < determinationAutomat[i][0].state.size(); j++) {
			for (size_t k = 0; k < finalStates.size(); k++)
				if (determinationAutomat[i][0].state[j] == finalStates[k])
				{
					determinationAutomat[i][0].isFinalState = true;
					finalStateFind = true;
					newFinalStates.push_back(i);
					break;
				}

			if(finalStateFind)
			{
				finalStateFind = false;
				break;
			}
		}
}

void ReadFinalStates(vector<int>& finalStates, int countOfFinalStates, ifstream& inFile) 
{
	for (size_t i = 0; i < countOfFinalStates; i++)
		inFile >> finalStates[i];
}

void ReadStartStateOfAutomat(vector<vector<State>>& startStateOfAutomat, int countOfStates, ifstream& inFile, vector<int> finalStates, int countOfInputStates)
{
	for(size_t i = 0; i < countOfStates; i++)
	{
		startStateOfAutomat[i][0].state.push_back(i);
		for (size_t k = 0; k < finalStates.size(); k++)
			if (finalStates[k] == i)
				startStateOfAutomat[i][0].isFinalState = true;
	}

    int i = 0;
	string lineWithStates;
	getline(inFile, lineWithStates);
	while(!inFile.eof())
	{
		getline(inFile, lineWithStates);
		if (lineWithStates.empty())
		{
			i++;
			continue;
		}

		string delim(" ");
		size_t prev = 0;
		size_t next;
		size_t delta = delim.length();
		int state;
		int inputSignal;
		string tmp;
		bool isWorking = true;
		while(isWorking)
		{
			next = lineWithStates.find(delim, prev);
			tmp = lineWithStates.substr(prev, next - prev);
			state = atoi(tmp.c_str());
			prev = next + delta;
			next = lineWithStates.find(delim, prev);

			if (next == string::npos)
			{
				isWorking = false;
				tmp = lineWithStates.substr(prev, lineWithStates.length());
			}else
				tmp = lineWithStates.substr(prev, next - prev);

			prev = next + delta;
			inputSignal = atoi(tmp.c_str()) + 1;

			startStateOfAutomat[i][inputSignal].state.push_back(state);
		}
		i++;
	}

	for (size_t i = 0; i < countOfStates; i++)
		for (size_t j = 1; j <= countOfInputStates; j++)
			if (startStateOfAutomat[i][j].state.size() == 0)
				startStateOfAutomat[i][j].state.push_back(NotState);

}

vector<vector<State>> GetDeterminateAutomat(vector<vector<State>> startStateOfAutomat, int countOfStates, int countOfInputStates)
{
	vector <vector<State>> determinationAutomat;
	AddStartStateToDeterminationAutomat(determinationAutomat, startStateOfAutomat, countOfInputStates);
	int lastIndex = 0;

	while (true)
	{
		for (size_t i = 1; i <= countOfInputStates; i++)
		{
			if(determinationAutomat[lastIndex][i].state[0] != -1)
				if (GetIndexIfStateFoundInAutomat(determinationAutomat, determinationAutomat[lastIndex][i]) == -1) 
				{
					AddNewStateToDeterminationAutomat(determinationAutomat, startStateOfAutomat, countOfInputStates, determinationAutomat[lastIndex][i]);
				}
		}

		lastIndex++;	

		if (lastIndex >= determinationAutomat.size())
			break;
	}

	return determinationAutomat;
}

void AddNewStateToDeterminationAutomat(vector<vector<State>>& determinationAutomat, vector<vector<State>> startAutomat, int countOfInputStates, State state)
{
	vector<State> newStateForDeterminateAutomat(countOfInputStates + 1);
	newStateForDeterminateAutomat[0].state = state.state;
	bool stateExist = false;
	set<int> setWithStates;
	for (size_t i = 1; i <= countOfInputStates; i++)
	{
		for (size_t j = 0; j < state.state.size(); j++)
			for (size_t k = 0; k < startAutomat[state.state[j]][i].state.size(); k++)
				if(startAutomat[state.state[j]][i].state[k] != -1)
					setWithStates.insert(startAutomat[state.state[j]][i].state[k]);

		if(setWithStates.empty())
			newStateForDeterminateAutomat[i].state.push_back(-1);

		for (int state : setWithStates)
			newStateForDeterminateAutomat[i].state.push_back(state);

		setWithStates.clear();
	}

	determinationAutomat.push_back(newStateForDeterminateAutomat);
}

int GetIndexIfStateFoundInAutomat(vector<vector<State>> determinationAutomat, State stateForCheck) 
{
	bool isFind = false;

	for (size_t i = 0; i < determinationAutomat.size(); i++) 
	{
		if (stateForCheck.state.size() == determinationAutomat[i][0].state.size())
		{ 
			for(size_t j = 0; j < stateForCheck.state.size(); j++)
			{
				for(size_t k = 0; k < stateForCheck.state.size(); k++)
				{
					if (stateForCheck.state[k] == determinationAutomat[i][0].state[j])
					{
						isFind = true;
						break;
					}
				}

				if (!isFind)
					break;

				if (isFind && j == stateForCheck.state.size() - 1)
					return i;
			}
		}
	}

	return -1;
}

void AddStartStateToDeterminationAutomat(vector<vector<State>>& determinationAutomat, vector<vector<State>> startStateOfAutomat, int countOfInputStates) 
{
	vector<State> newState(countOfInputStates + 1);

	for (size_t i = 0; i <= countOfInputStates; i++) {
		newState[i] = startStateOfAutomat[0][i];
	}

	determinationAutomat.push_back(newState);
}


void ShowAutomat(vector<vector<State>>& startStateOfAutomat, int countOfStates, int countOfInputStates)
{
	for (size_t i = 0; i < countOfStates; i++)
	{
		for (size_t j = 0; j <= countOfInputStates; j++)
		{
			if (j == 0)
			{
				cout << "State: ";
				for (size_t k = 0; k < startStateOfAutomat[i][j].state.size(); k++)
					cout << startStateOfAutomat[i][j].state[k] << ' ';
				if (startStateOfAutomat[i][j].isFinalState)
					cout << "true: ";
				else
					cout << "false: ";
			}
			else
			{
				for (size_t k = 0; k < startStateOfAutomat[i][j].state.size(); k++)
					cout << startStateOfAutomat[i][j].state[k] << ' ';
			}
		}
		cout << endl;
	}
}