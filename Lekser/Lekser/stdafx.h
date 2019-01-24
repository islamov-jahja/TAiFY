// stdafx.h: включаемый файл для стандартных системных включаемых файлов
// или включаемых файлов для конкретного проекта, которые часто используются, но
// не часто изменяются
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <map>
#include <utility>
using namespace std;

struct Terminal 
{
	string terminal;
	int posX;
	int posY;
};

struct TerminalAndValue 
{
	Terminal terminal;
	int value;

};



// TODO: Установите здесь ссылки на дополнительные заголовки, требующиеся для программы
