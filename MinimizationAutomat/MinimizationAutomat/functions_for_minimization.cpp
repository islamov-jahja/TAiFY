#include "stdafx.h"
#include "functions_for_minimization.h"

void ReadMur(vector<vector<TransitionAndOutputState>> & arrOfMur, ifstream & inFile, size_t countOfInputState, size_t countOfState)
{
	vector<vector<int>> arrOfMurI(countOfInputState + 1, vector<int>(countOfState));

	for (size_t i = 0; i < countOfInputState + 1; i++)
		for (size_t j = 0; j < countOfState; j++)
			inFile >> arrOfMurI[i][j];

	for (size_t i = 0; i < countOfState; i++)
		for (size_t j = 0; j < countOfInputState; j++)
		{
			arrOfMur[j][i].transition = arrOfMurI[j + 1][i];
			arrOfMur[j][i].outPutstate = arrOfMurI[0][i];
		}
}

void ReadMili(vector<vector<TransitionAndOutputState>> & arrOfMili, ifstream & inFile, size_t countOfInputState, size_t countOfState)
{
	for (size_t i = 0; i < countOfInputState; i++)
		for (size_t j = 0; j < countOfState; j++)
		{
			inFile >> arrOfMili[i][j].transition;
			inFile >> arrOfMili[i][j].outPutstate;
		}
}

vector<vector<TransitionAndOutputState>> GetArrWithMinimizedMili(ofstream & outFile, ifstream & inFile, size_t countOfInputState, size_t countOfOuputState, size_t countOfState, size_t graphForm)
{
	vector<vector<TransitionAndOutputState>> arrOfMili(countOfInputState, vector<TransitionAndOutputState>(countOfState));

	ReadMili(arrOfMili, inFile, countOfInputState, countOfState);
	PrintGraph(arrOfMili, countOfState, countOfInputState, "inMili.dot");
	vector<vector<int>> arrWithEquvivalents(countOfInputState + 2, vector<int>(countOfState));
	arrWithEquvivalents = GetArrFromFirstIt(arrOfMili, countOfInputState, countOfState);
	arrWithEquvivalents = GetSplittingGraph(arrWithEquvivalents, arrOfMili, countOfInputState, countOfState);

	int counter = 0;

	for (size_t i = 0; i < countOfState; i++)
		if (counter < arrWithEquvivalents[0][i])
			counter = arrWithEquvivalents[0][i];
	counter++;

	vector<vector<TransitionAndOutputState>> arrOfMiliForOut = GetGraphInAnotherForm(arrWithEquvivalents, arrOfMili, countOfInputState, countOfState, counter);
	PrintGraph(arrOfMiliForOut, counter, countOfInputState, "outMili.dot");
	PrintArr(arrOfMiliForOut, countOfInputState, counter, outFile, graphForm, countOfOuputState);
	return arrOfMiliForOut;
}

vector<vector<TransitionAndOutputState>> GetArrWithMinimizedMur(ofstream & outFile, ifstream & inFile, size_t countOfInputState, size_t countOfOuputState, size_t countOfState, size_t graphFrom)
{
	vector<vector<TransitionAndOutputState>> arrOfMur(countOfInputState, vector<TransitionAndOutputState>(countOfState));
	ReadMur(arrOfMur, inFile, countOfInputState, countOfState);
	PrintGraph(arrOfMur, countOfState, countOfInputState, "inMur.dot");
	vector<vector<int>> arrWithEquvivalents(countOfInputState + 2, vector<int>(countOfState));
	arrWithEquvivalents = GetArrFromFirstIt(arrOfMur, countOfInputState, countOfState);
	arrWithEquvivalents = GetSplittingGraph(arrWithEquvivalents, arrOfMur, countOfInputState, countOfState);

	int counter = 0;

	for (size_t i = 0; i < countOfState; i++)
		if (counter < arrWithEquvivalents[0][i])
			counter = arrWithEquvivalents[0][i];
	counter++;

	vector<vector<TransitionAndOutputState>> arrOfMurForOut = GetGraphInAnotherForm(arrWithEquvivalents, arrOfMur, countOfInputState, countOfState, counter);;
	PrintGraph(arrOfMurForOut, counter, countOfInputState, "outMur.dot");
	PrintArr(arrOfMurForOut, countOfInputState, counter, outFile, graphFrom, countOfOuputState);
	return arrOfMurForOut;
}

vector<vector<TransitionAndOutputState>> GetGraphInAnotherForm(vector<vector<int>> arrWithEquvivalents, vector<vector<TransitionAndOutputState>> arrOfGraph, int countOfInputState, int countOfState, int counter)
{
	vector<vector<TransitionAndOutputState>> arrForOut(countOfInputState, vector<TransitionAndOutputState>(counter));
	counter = 0;

	for (size_t i = 0; i < countOfState; i++)
		if (i == 0)
		{
			counter = arrWithEquvivalents[0][i];
			for (size_t j = 0; j < countOfInputState; j++)
			{
				arrForOut[j][counter].transition = arrWithEquvivalents[j + 2][i];
				arrForOut[j][counter].outPutstate = arrOfGraph[j][arrWithEquvivalents[1][i]].outPutstate;
			}
		}
		else
		{
			if (counter != arrWithEquvivalents[0][i])
			{
				counter = arrWithEquvivalents[0][i];
				for (size_t j = 0; j < countOfInputState; j++)
				{
					arrForOut[j][counter].transition = arrWithEquvivalents[j + 2][i];
					arrForOut[j][counter].outPutstate = arrOfGraph[j][arrWithEquvivalents[1][i]].outPutstate;
				}
			}
		}

	return arrForOut;
}

vector<vector<int>> GetArrFromFirstIt(vector<vector<TransitionAndOutputState>> arrOfMili, size_t countOfInputState, size_t countOfState)
{
	int counter = 0;
	vector<vector<int>> arrForOut(countOfInputState + 2, vector<int>(countOfState));
	set<int> setWithStates;
	bool isEquivalent = true;
	int countEquivalent = 0;
	int countForCheck = 0;
	set<int> setForCheck;

	for (size_t i = 0; i < countOfState; i++)
	{
		setForCheck = setWithStates;
		countForCheck = setWithStates.size();

		for (size_t j = i; j < countOfState; j++)
		{
			for (size_t k = 0; k < countOfInputState; k++)
				if (!(arrOfMili[k][i].outPutstate == arrOfMili[k][j].outPutstate && setWithStates.find(j) == setWithStates.end()))
				{
					isEquivalent = false;
					break;
				}

			if (isEquivalent)
				setWithStates.insert(j);
			else
				isEquivalent = true;
		}

		if (countForCheck != setWithStates.size())
		{
			bool isCheck = false;

			for (auto x : setWithStates)
			{
				isCheck = false;

				for (auto y : setForCheck)
					if (x == y)
						isCheck = true;

				if (!isCheck)
				{
					arrForOut[0][counter] = countEquivalent;
					arrForOut[1][counter] = x;
					counter++;
				}
			}
			countEquivalent++;
		}
	}

	return arrForOut;
}

vector<vector<int>> GetSplittingGraph(vector<vector<int>> arrFromFirstIt, vector<vector<TransitionAndOutputState>> startArr, int countInputState, int countOfState)
{
	vector<vector<int>> checkArr(countInputState + 2, vector<int>(countOfState));

	while (true)
	{
		if (checkArr == arrFromFirstIt)
		{
			arrFromFirstIt = GetFilledArray(arrFromFirstIt, startArr, countInputState, countOfState);
			break;
		}

		checkArr = arrFromFirstIt;
		arrFromFirstIt = GetFilledArray(arrFromFirstIt, startArr, countInputState, countOfState);
		arrFromFirstIt = GetSplit(arrFromFirstIt, countInputState, countOfState);
	}

	return arrFromFirstIt;
}

vector<vector<int>> GetFilledArray(vector<vector<int>> arrFromFirstIt, vector<vector<TransitionAndOutputState>> startArr, int countInputState, int countOfState)
{
	for (size_t i = 0; i < countOfState; i++)
		for (size_t j = 0; j < countInputState; j++)
		{
			int index = -1;
			for (size_t k = 0; k < countOfState; k++)
				if (arrFromFirstIt[1][k] == startArr[j][arrFromFirstIt[1][i]].transition)
				{
					index = arrFromFirstIt[0][k];
					break;
				}

			arrFromFirstIt[j + 2][i] = index;
		}

	return arrFromFirstIt;
}

vector<vector<int>> GetSplit(vector<vector<int>> arrFromFirstIt, int countOfInputState, int countOfState)
{
	vector<vector<int>> arrForOut(countOfInputState + 2, vector<int>(countOfState));
	set<int> setForCheck;
	set<int> mySet;
	bool isCheck = true;
	int countEqvivalent = 0;
	int counter = 0;

	for (size_t i = 0; i < countOfState; i++)
	{
		mySet = setForCheck;
		for (size_t j = 0; j < countOfState; j++)
		{
			for (size_t k = 0; k < countOfInputState; k++)
			{
				if (arrFromFirstIt[k + 2][i] != arrFromFirstIt[k + 2][j] || setForCheck.find(j) != setForCheck.end() || arrFromFirstIt[0][i] != arrFromFirstIt[0][j])
					isCheck = false;
			}

			if (isCheck)
			{
				setForCheck.insert(j);
				arrForOut[0][counter] = countEqvivalent;
				arrForOut[1][counter] = arrFromFirstIt[1][j];
				counter++;
			}
			else
				isCheck = true;
		}

		if (mySet.size() != setForCheck.size())
			countEqvivalent++;
	}

	return arrForOut;
}

void PrintGraph(vector<vector<TransitionAndOutputState>> arrGraph, int countOfState, int countOfInputState, string fileName)
{
	using Edge = pair<int, int>;
	using Graph = boost::adjacency_list<vecS, vecS, directedS, property<vertex_color_t, default_color_type>, property<edge_weight_t, string>>;
	const int VERTEX_COUNT = countOfState;

	vector<Edge> edges;
	for (size_t i = 0; i < countOfState; i++)
		for (size_t j = 0; j < countOfInputState; j++)
			edges.push_back(pair<int, int>(i, arrGraph[j][i].transition));

	vector<string> weights;
	for (size_t i = 0; i < countOfState; i++)
		for (size_t j = 0; j < countOfInputState; j++)
			weights.push_back(to_string(j + 1) + '/' + to_string(arrGraph[j][i].outPutstate));

	Graph graph(edges.begin(), edges.end(), weights.begin(), VERTEX_COUNT);
	dynamic_properties dp;

	dp.property("weight", get(edge_weight, graph));
	dp.property("label", get(edge_weight, graph));
	dp.property("node_id", get(vertex_index, graph));
	ofstream ofs(fileName);
	write_graphviz_dp(ofs, graph, dp);
}

void PrintArr(vector<vector<TransitionAndOutputState>> arrGraph, int countIn, int countAll, ofstream & outFile, int formGraph, int outCount)
{
	outFile << formGraph << endl;
	outFile << countIn << endl;
	outFile << outCount << endl;
	outFile << countAll << endl;
	if (formGraph == MILI)
		for (size_t i = 0; i < countIn; i++)
		{
			for (size_t j = 0; j < countAll; j++)
				outFile << arrGraph[i][j].transition << ' ' << arrGraph[i][j].outPutstate << ' ';
			outFile << endl;
		}
	else
	{
		for (size_t i = 0; i < countAll; i++)
			outFile << arrGraph[0][i].outPutstate << ' ';
		outFile << endl;

		for (size_t i = 0; i < countIn; i++)
		{
			for (size_t j = 0; j < countAll; j++)
				outFile << arrGraph[i][j].transition << ' ';
			outFile << endl;
		}
	}
}