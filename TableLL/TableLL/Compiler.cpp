#include "stdafx.h"
#include "Compiler.h"


Compiler::Compiler(string nameOfFile):_nameOfFile(nameOfFile)
{
	ToInitialize();
	FillQueueTerminalsForWrite();
	DefineGuideSet();
	FillTable();
}


Compiler::~Compiler()
{
}

void Compiler::addingTerminalToSet(int index, char terminal)
{
	int startIndex = _descriptionOfRules[index].find('/');

	for (int i = 0; i < _descriptionOfRules.size(); i++)
	{
		string line = _descriptionOfRules[i].substr(1, _descriptionOfRules[i].size());
		int numberOfSymbol = line.find(terminal);

		if (numberOfSymbol != -1 && numberOfSymbol+2 != _descriptionOfRules[i].find('/'))
		{
			char nextTerminal = _descriptionOfRules[i][numberOfSymbol+2];

			for (int j = 0; j < _descriptionOfRules.size(); j++)
			{
				if (_descriptionOfRules[j][0] == nextTerminal)
				{
					int indexOfDelimeter = _descriptionOfRules[j].find('/');

					for (int k = indexOfDelimeter + 1; k < _descriptionOfRules[j].size(); k++)
					{
						line = _descriptionOfRules[index].substr(startIndex, _descriptionOfRules[index].size());
						
						if (line.find(_descriptionOfRules[j][k]) == -1)
						{
							_descriptionOfRules[index].push_back(_descriptionOfRules[j][k]);
						}
					}
				}
			}
		}
	}
}

string Compiler::GetAllGuideSetOfComponent(char component)
{
	string guideSet;
	int startIndex = -1;
	int finishIndex = 0;

	for (int i = 0; i < _descriptionOfRules.size(); i++)
	{
		if (_descriptionOfRules[i][0] == component && startIndex == -1)
			startIndex = i;

		if (startIndex != -1 && component != _descriptionOfRules[i][0])
		{
			finishIndex = i -1;
			break;
		}	
	}

	if (finishIndex == 0)
		finishIndex = _descriptionOfRules.size() - 1;

	for (int i = startIndex; i <= finishIndex; i++)
	{
		for (int j = _descriptionOfRules[i].find('/') + 1; j < _descriptionOfRules[i].size(); j++)
		{
			if (guideSet.find(_descriptionOfRules[i][j]) == -1)
				guideSet.push_back(_descriptionOfRules[i][j]);
		}
	}

	return guideSet;
}

string Compiler::GetEndTerminals()
{
	string endTerminals;

	char terminal = _descriptionOfRules[0][0];

	for (int i = 0; i < _descriptionOfRules.size(); i++)
	{
		if (_descriptionOfRules[i][0] == terminal)
		{
			endTerminals.push_back(_descriptionOfRules[i][_descriptionOfRules[i].find('/') - 1]);
		}
	}


	return endTerminals;
}

void Compiler::FillQueueTerminalsForWrite()
{
	int startIndex = 0;
	int endIndex = 0;
	int checkEndIndex = -1;
	char symbol;

	while (true)
	{
		checkEndIndex = endIndex;
		if (startIndex >= _descriptionOfRules.size())
			break;

		symbol = _descriptionOfRules[startIndex][0];

		for (int i = startIndex; i < _descriptionOfRules.size(); i++)
		{
			if (_descriptionOfRules[i][0] != symbol)
			{
				endIndex = i - 1;
				break;
			}
		}
		if (checkEndIndex == endIndex)
			endIndex = _descriptionOfRules.size() - 1;

		for (int i = startIndex; i <= endIndex; i++)
		{
			StructForQueue newObject;
			newObject.rule = '-1';
			newObject.i = i;
			newObject.j = 0;
			newObject.terminal = _descriptionOfRules[i][0];
			_queue.push_back(newObject);
		}

		for (int i = startIndex; i <= endIndex; i++)
		{
			for (int j = 1; j < _descriptionOfRules[i].size(); j++)
			{
				StructForQueue newObject;
				newObject.rule = _descriptionOfRules[i][0];;
				newObject.i = i; 
				newObject.j = j;
				newObject.terminal = _descriptionOfRules[i][j];
				_queue.push_back(newObject);
			}
		}

		startIndex = endIndex + 1;
	}
}

void Compiler::FillTable()
{
	string endTerminals = GetEndTerminals();

	for (int i = 0; i < _queue.size(); i++)
	{
		string line;
		StructForQueue elementOfQueue = _queue[i];

		vector<string> table;
		line.push_back(elementOfQueue.terminal);

		table.push_back(to_string(i)); //номер

		table.push_back(line); // название терминала

		if (elementOfQueue.j == 0) //если главный компонент
		{
			line = _descriptionOfRules[elementOfQueue.i].substr(_descriptionOfRules[elementOfQueue.i].find('/') + 1, _descriptionOfRules[elementOfQueue.i].size());
			table.push_back(line); //направляющее множество

			line = '0';
			table.push_back(line);//сдвиг

			if (i != _queue.size() - 1)
			{
				if (_queue[i + 1].terminal != elementOfQueue.terminal && _queue[i + 1].j != 0)
				{
					table.push_back("1");//error
				}
				else
				{
					table.push_back("0");//error
				}
			}
			else
			{
				table.push_back("0");//error
			}

			table.push_back("0");//стек

			for (int j = 0; j < _queue.size(); j++)
			{
				string term;
				term.push_back(_queue[j].terminal);

				if (_descriptionOfRules[elementOfQueue.i][elementOfQueue.j + 1] == EPSILON)
				{
					if (_queue[j].terminal == EPSILON)
					{
						table.push_back(to_string(j)); // GOTO
						break;
					}
				}
				else
				{
					if (term == table[2])
					{
						table.push_back(to_string(j)); // GOTO
						break;
					}
				}
			}

			table.push_back("0"); //END

		}
		else //подкомпонент
		{
			if ('A' <= elementOfQueue.terminal && elementOfQueue.terminal <= 'Z') //какой то теминал
			{
				line = GetAllGuideSetOfComponent(elementOfQueue.terminal);
				table.push_back(line); // направляющее множество

				table.push_back("0"); // сдвиг

				table.push_back("-1"); // Error

				if (_descriptionOfRules[elementOfQueue.i][elementOfQueue.j + 1] != '/')
				{
					table.push_back("1");//стек
				}
				else
				{
					table.push_back("0");//стек
				}

				for (int j = 0; j < _queue.size(); j++)
				{
					if (_queue[j].terminal == elementOfQueue.terminal && _queue[j].j == 0)
					{
						table.push_back(to_string(j));//GOTO
						break;
					}
				}

				if (endTerminals.find(elementOfQueue.terminal) != -1 && elementOfQueue.rule == 'S')
				{
					table.push_back("1"); //END
				}else
					table.push_back("0"); //END
			}
			else//просто символ
			{
				if (elementOfQueue.terminal == EPSILON)
				{
					line = _descriptionOfRules[elementOfQueue.i].substr(_descriptionOfRules[elementOfQueue.i].find('/') + 1, _descriptionOfRules[elementOfQueue.i].size());
					table.push_back(line); //направляющее множество
				}
				else
				{
					table.push_back(line); // направляющее множество
				}

				table.push_back("1"); // сдвиг
 
				table.push_back("1"); // Error

				table.push_back("0");//стек

				if (elementOfQueue.terminal == EPSILON)
				{
					table.push_back("-1");//GOTO
				}
				else
				{
					if (_descriptionOfRules[elementOfQueue.i][elementOfQueue.j + 1] != '/')
					{
						table.push_back(to_string(i + 1)); //GOTO
					}
					else
					{
						table.push_back("-1"); //GOTO
					}
				}

				if (endTerminals.find(elementOfQueue.terminal) != -1 && elementOfQueue.rule == 'S')
				{
					table.push_back("1"); //END
				}
				else
					table.push_back("0"); //END
			}
		}

		_table.push_back(table);
	}

}

string Compiler::GetGiudeSetToBigTerminal(int index, char terminal)
{
	string newGuideTerminal = _descriptionOfRules[index];
	newGuideTerminal.push_back('/');

	for (int i = 0; i < _descriptionOfRules.size(); i++)
	{
		if (_descriptionOfRules[i][0] == terminal)
		{
			if (_descriptionOfRules[i].find('/') != -1)
			{
				string lineToCheck = newGuideTerminal.substr(newGuideTerminal.find('/'), newGuideTerminal.size());
				for (int j = _descriptionOfRules[i].find('/')+1; j < _descriptionOfRules[i].size(); j++)
				{
					if (lineToCheck.find(_descriptionOfRules[i][j]) == -1)
						newGuideTerminal.push_back(_descriptionOfRules[i][j]);
				}
			}
			else
				return _descriptionOfRules[index];
		}
	}

	return newGuideTerminal;
}

void Compiler::AddGuideSetForEpsilon()
{
	for (int i = 0; i < _descriptionOfRules.size(); i++)
	{
		if (_descriptionOfRules[i][1] == EPSILON)
		{
			_descriptionOfRules[i].push_back('/');
			_descriptionOfRules[i].push_back(EMPTY_CHARACTER);
			char terminal = _descriptionOfRules[i][0];
			addingTerminalToSet(i, terminal);
		}
	}
}

bool Compiler::GuideSetIsDefined()
{
	int pos = -1;
	for (int i = 0; i < _descriptionOfRules.size(); i++)
	{
		pos = _descriptionOfRules[i].find("/");
		if (pos == -1 && _descriptionOfRules[i][1] != EPSILON)
			return false;
	}

	return true;
}

void Compiler::AddIterationGuideSet()
{
	for (int i = 0; i < _descriptionOfRules.size(); i++)
	{
		if (_descriptionOfRules[i][1] != EPSILON && _descriptionOfRules[i].find('/') == -1)
		{
			if ('A' <= _descriptionOfRules[i][1] && _descriptionOfRules[i][1] <= 'Z')
			{
				_descriptionOfRules[i] = GetGiudeSetToBigTerminal(i, _descriptionOfRules[i][1]);
			}
			else
			{
				_descriptionOfRules[i].push_back('/');
				_descriptionOfRules[i].push_back(_descriptionOfRules[i][1]);
			}
		}
	}
}

void Compiler::DefineGuideSet()
{
	while (!GuideSetIsDefined())
	{
		AddIterationGuideSet();
	}

	AddGuideSetForEpsilon();
}

void Compiler::ToInitialize()
{
	ifstream fileWithRules(_nameOfFile);
	vector<string> arr;
	string line;

	while (!fileWithRules.eof())
	{
		getline(fileWithRules, line);
		string line2;

		for (int i = 0; i < line.size(); i += 2)
			line2.push_back(line[i]);
		
		_descriptionOfRules.push_back(line2);
	}
}


void Compiler::ShowDescription()
{
	string line;
	for (int i = 0; i < _descriptionOfRules.size(); i++)
	{
		cout << _descriptionOfRules[i] << endl;
	}
}

void Compiler::ShowQueue()
{
	for each ( StructForQueue value in _queue)
	{
		cout << value.terminal << ' ' << value.i << ' ' << value.j << ' ' << value.rule << endl;
	}
}

void Compiler::ShowTable()
{
	cout << "N" << "      " << "T" << "       " << "Shift" << "      " << "Error" << "      " << "Stack" << "      " << "GoTo" << "      " << "End" << endl << endl;
	for (int i = 0; i < _table.size(); i++)
	{
		for (int j = 0; j < _table[i].size(); j++)
		{
			cout << _table[i][j] << "      ";
		}

		cout << endl << endl;
	}
}
