// TableLL.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Compiler.h"


int main()
{
	Compiler compiler("rule.txt");
	cout << "show------------------------------------------" << endl;
	compiler.ShowDescription();
	cout << endl;
	compiler.ShowQueue();
	cout << endl;
	compiler.ShowTable();
	system("pause");
    return 0;
}

