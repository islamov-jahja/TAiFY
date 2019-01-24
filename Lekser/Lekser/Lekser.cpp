// Lekser.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Compiler.h"

int main()
{
	Compiler compiler("input.txt");
	TerminalAndValue terminalAndValue;
	Terminal terminal;

	terminal.terminal = "aba";

	while (!terminal.terminal.empty())
	{
		terminalAndValue = compiler.getNextTerminal();
		terminal = terminalAndValue.terminal;
		if (terminal.terminal.empty())
			break;

		if (terminalAndValue.value == 0)
			cout << "Error: Key word: " << terminal.terminal << " line " << terminal.posY << " position " << terminal.posX << endl;
		else
			cout << "Key word: " << terminal.terminal << " id: " << terminalAndValue.value << " line " << terminal.posY << " position " << terminal.posX << endl;
	}

	system("pause");
    return 0;
}

