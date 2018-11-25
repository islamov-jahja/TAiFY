#pragma once
struct TransitionAndOutputState
{
	int transition;//переход
	int outPutstate;//выходное состояние
};

void ReadMili(vector<vector<TransitionAndOutputState>> & arrOfMili, ifstream & inFile, size_t countOfInputState, size_t countOfState);
vector<vector<TransitionAndOutputState>> GetArrWithMinimizedMili(ofstream & outFile, ifstream & inFile, size_t countOfInputState, size_t countOfOuputState, size_t countOfState, size_t graphFrom);
vector<vector<TransitionAndOutputState>> GetArrWithMinimizedMur(ofstream & outFile, ifstream & inFile, size_t countOfInputState, size_t countOfOuputState, size_t countOfState, size_t graphFrom);
vector<vector<int>> GetArrFromFirstIt(vector<vector<TransitionAndOutputState>> arrOfMili, size_t countOfInputState, size_t countOfState);
void ReadMur(vector<vector<int>> & arrofMur, ifstream & inFile, size_t countOfInputState, size_t countOfState);
void PrintGraph(vector<vector<TransitionAndOutputState>> arrOfMili, int countOfState, int countOfInputState, string fileName);
vector<vector<int>> GetSplittingGraph(vector<vector<int>> arrFromFirstIt, vector<vector<TransitionAndOutputState>> startArr, int coutInputState, int countOfState);
vector<vector<int>> GetSplit(vector<vector<int>> arrFromFirstIt, int countOfInputState, int countOfState);
vector<vector<int>> GetFilledArray(vector<vector<int>> arrFromFirstIt, vector<vector<TransitionAndOutputState>> startArr, int countInputState, int countOfState);
vector<vector<TransitionAndOutputState>> GetGraphInAnotherForm(vector<vector<int>> arrWithEquvivalents, vector<vector<TransitionAndOutputState>> arrOfMur, int countOfInputState, int countOfState, int counter);
void PrintArr(vector<vector<TransitionAndOutputState>> arrGraph, int countIn, int countAll, ofstream & outFile, int formGraph, int outCount);

const int MUR = 1;
const int MILI = 2;

