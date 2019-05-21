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
#include <vector>
#include <string>

struct StructForQueue
{
	char terminal;
	int i;
	int j;
};

const char EPSILON = '*';
const char EMPTY_CHARACTER = '|';
using namespace std;



// TODO: Установите здесь ссылки на дополнительные заголовки, требующиеся для программы
