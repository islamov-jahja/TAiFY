#pragma once
class Compiler
{
public:
	Compiler(string nameOfFile);
	void ShowDescription();
	void ShowQueue();
	void ShowTable();
	~Compiler();
private:
	string GetAllGuideSetOfComponent(char component);
	string GetEndTerminals();
	void FillQueueTerminalsForWrite();
	void FillTable();
	string GetGiudeSetToBigTerminal(int index, char terminal);
	void AddGuideSetForEpsilon();
	void addingTerminalToSet(int index, char terminal);
	bool GuideSetIsDefined();
	void AddIterationGuideSet();
	void DefineGuideSet();
	void ToInitialize();
	vector<vector<string>> _table;
	string _nameOfFile;
	vector<string> _descriptionOfRules;
	vector<StructForQueue> _queue;
};

