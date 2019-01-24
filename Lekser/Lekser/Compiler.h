#pragma once
class Compiler
{
public:
	Compiler(string nameOfFile);
	TerminalAndValue getNextTerminal();
	~Compiler();
private:
	Terminal getTerminal();
	int getValueOfTerminal(string terminal);
	bool isIdentifier(string terminal);
	bool isInteger(string terminal);
	bool isInt2(string terminal);
	bool isInt8(string terminal);
	bool isInt16(string terminal);
	bool isFloat(string terminal);
	bool isFloatE(string terminal);
	ifstream fileWithCode;
	int posX;
	int posY;
	bool isComment;
	map<string, int> mapWithKey;
};

