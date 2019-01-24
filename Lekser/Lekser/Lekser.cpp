// Lekser.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Compiler.h"

int main()
{
	Compiler compiler("input.txt");
	TerminalAndValue terminalAndValue;
	Terminal terminal;

	terminalAndValue = compiler.getNextTerminal();
	terminal = terminalAndValue.terminal;
	cout << terminal.terminal << ' ' << terminalAndValue.value << ' ' << terminal.posY << ' ' << terminal.posX << endl;
	terminalAndValue = compiler.getNextTerminal();
	terminal = terminalAndValue.terminal;
	cout << terminal.terminal << ' ' << terminalAndValue.value << ' ' << terminal.posY << ' ' << terminal.posX << endl;
	terminalAndValue = compiler.getNextTerminal();
	terminal = terminalAndValue.terminal;
	cout << terminal.terminal << ' ' << terminalAndValue.value << ' ' << terminal.posY << ' ' << terminal.posX << endl;
	terminalAndValue = compiler.getNextTerminal();
	terminal = terminalAndValue.terminal;
	cout << terminal.terminal << ' ' << terminalAndValue.value << ' ' << terminal.posY << ' ' << terminal.posX << endl;
	terminalAndValue = compiler.getNextTerminal();
	terminal = terminalAndValue.terminal;
	cout << terminal.terminal << ' ' << terminalAndValue.value << ' ' << terminal.posY << ' ' << terminal.posX << endl;
	terminalAndValue = compiler.getNextTerminal();
	terminal = terminalAndValue.terminal;
	cout << terminal.terminal << ' ' << terminalAndValue.value << ' ' << terminal.posY << ' ' << terminal.posX << endl;
	terminalAndValue = compiler.getNextTerminal();
	terminal = terminalAndValue.terminal;
	cout << terminal.terminal << ' ' << terminalAndValue.value << ' ' << terminal.posY << ' ' << terminal.posX << endl;
	terminalAndValue = compiler.getNextTerminal();
	terminal = terminalAndValue.terminal;
	cout << terminal.terminal << ' ' << terminalAndValue.value << ' ' << terminal.posY << ' ' << terminal.posX << endl;
	terminalAndValue = compiler.getNextTerminal();
	terminal = terminalAndValue.terminal;
	cout << terminal.terminal << ' ' << terminalAndValue.value << ' ' << terminal.posY << ' ' << terminal.posX << endl;
	terminalAndValue = compiler.getNextTerminal();
	terminal = terminalAndValue.terminal;
	cout << terminal.terminal << ' ' << terminalAndValue.value << ' ' << terminal.posY << ' ' << terminal.posX << endl;
	terminalAndValue = compiler.getNextTerminal();
	terminal = terminalAndValue.terminal;
	cout << terminal.terminal << ' ' << terminalAndValue.value << ' ' << terminal.posY << ' ' << terminal.posX << endl;

	system("pause");
    return 0;
}

