#include "stdafx.h"
#include "Compiler.h"


Compiler::Compiler(string nameOfFile)
{
	fileWithCode.open(nameOfFile);
	posX = 1;
	posY = 1;
	isComment = false;
	ifstream fileWithKeys("fileWithKeyWord.txt");

	while (!fileWithKeys.eof())
	{
		pair<string, int> pairOfTerminalAndValue;
		fileWithKeys >> pairOfTerminalAndValue.first;
		fileWithKeys >> pairOfTerminalAndValue.second;
		mapWithKey.insert(pairOfTerminalAndValue);
	}
}

TerminalAndValue Compiler::getNextTerminal()
{
	TerminalAndValue returnVariable;
	returnVariable.terminal = getTerminal();

	if (returnVariable.terminal.terminal.find("\*") == 1)
	{
		isComment = true;
	}
	else
	{
		returnVariable.value = getValueOfTerminal(returnVariable.terminal.terminal);
		return returnVariable;
	}

	while(isComment)
	{
		returnVariable.terminal = getTerminal();
		if (returnVariable.terminal.terminal.find("*/") == 0)
		{
			isComment = false;
		}

		if (returnVariable.terminal.terminal.empty())
		{
			returnVariable.terminal.terminal.clear();
			return returnVariable;
		}
	}

	returnVariable.terminal = getTerminal();
	returnVariable.value = getValueOfTerminal(returnVariable.terminal.terminal);

	return returnVariable;
}


Compiler::~Compiler()
{
	fileWithCode.close();
}

Terminal Compiler::getTerminal()
{
	string value;
	Terminal terminal;
	value.clear();
	char ch;

	if (fileWithCode.eof())
	{
		terminal.terminal = value;
		terminal.posX = posX;
		terminal.posY = posY;
		return terminal;
	}

	while (true)
	{
		ch = '\n';
		fileWithCode.get(ch);
		posX++;

		if (ch == '\n')
		{
			terminal.terminal = value;
			terminal.posX = posX-2;
			terminal.posY = posY;

			if (!fileWithCode.eof())
			{
				posX = 1;
				posY++;
			}
			break;
		}

		if (ch == ' ' && value.empty())
		{
			continue;
		}

		if (ch == ' ' && !value.empty()) {
			terminal.terminal = value;
			terminal.posX = posX-2;
			terminal.posY = posY;
			break;
		}

		value += ch;
	}

	return terminal;
}

int Compiler::getValueOfTerminal(string terminal)
{
	if (mapWithKey.find(terminal) != mapWithKey.cend())
		return mapWithKey.find(terminal)->second;

	if (isIdentifier(terminal))
		return 10;

	if (isInteger(terminal))
		return 11;

	if (isInt2(terminal))
		return 12;

	if (isInt8(terminal))
		return 13;

	if (isInt16(terminal))
		return 14;

	if (isFloat(terminal))
		return 15;

	if (isFloatE(terminal))
		return 16;

	return 0;
}

bool Compiler::isIdentifier(string terminal)
{
	for (int i = 0; i < terminal.size(); i++) {
		if (i == 0) 
		{
			if (!isalpha(terminal[i]) && terminal[i] != '_')
				return false;
		}

		if (i != 0)
		{
			if (!isalpha(terminal[i]) && !isdigit(terminal[i]) && terminal[i] != '_')
				return false;
		}
	}

	return true;
}

bool Compiler::isInteger(string terminal)
{
	int startIndex = 0;
	if (terminal[0] == '-')
		startIndex = 1;

	for (int i = startIndex; i < terminal.size(); i++)
		if (!isdigit(terminal[i]))
			return false;

	return true;
}

bool Compiler::isInt2(string terminal)
{
	if (terminal[terminal.size() - 1] != 'B')
		return false;

	for (int i = 0; i < terminal.size() - 1; i++)
		if (!isdigit(terminal[i]) || (terminal[i] < '0' || terminal[i] > '1'))
			return false;

	return true;
}

bool Compiler::isInt8(string terminal)
{
	if (terminal[terminal.size() - 1] != 'O')
		return false;

	for (int i = 0; i < terminal.size() - 1; i++)
		if (!isdigit(terminal[i]) || (terminal[i] < '0' || terminal[i] > '7'))
			return false;

	return true;
}

bool Compiler::isInt16(string terminal)
{
	if (terminal[terminal.size() - 1] != 'H')
		return false;

	for (int i = 0; i < terminal.size()-1; i++)
		if (!isdigit(terminal[i]) && (terminal[i] < 'A' || terminal[i] > 'F'))
			return false;

	return true;
}

bool Compiler::isFloat(string terminal)
{
	if (terminal[terminal.size() - 1] != 'f')
		return false;

	int countOfPoints = 0;
	int startIndex = 0;
	if (terminal[0] == '-')
		startIndex = 1;

	if (!isdigit(terminal[startIndex]))
		return false;

	startIndex++;

	for (int i = startIndex; i < terminal.size() - 1; i++)
	{
		if (!isdigit(terminal[i]) && terminal[i] != '.')
			return false;

		if (terminal[i] == '.')
			countOfPoints++;
		if (countOfPoints > 1)
			return false;
	}

	return true;
}

bool Compiler::isFloatE(string terminal)
{
	int countOfPoints = 0;
	int countOfE = 0;
	int startIndex = 0;
	if (terminal[0] == '-')
		startIndex = 1;

	if (!isdigit(terminal[startIndex]))
		return false;

	int indexToContinue = -1;
	startIndex++;

	for (int i = startIndex; i < terminal.size() - 1; i++)
	{
		if (i == indexToContinue)
			continue;

		if (!isdigit(terminal[i]) && terminal[i] != '.' && terminal[i] != 'E')
			return false;

		if (terminal[i] == '.')
			countOfPoints++;

		if (terminal[i] == 'E')
		{
			countOfE++;
			indexToContinue = i + 1;
			if (indexToContinue < terminal.size())
			{
				if (terminal[indexToContinue] != '-' && terminal[indexToContinue] != '+')
					return false;
			}

			if (indexToContinue == terminal.size() - 1)
				return false;
		}

		if (countOfPoints > 1 || countOfE > 1)
			return false;
	}

	return true;
}


