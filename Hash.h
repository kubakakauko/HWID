#pragma once
#include <string>
#include <iostream>
#include <Windows.h>
#include <iostream>
#include <tchar.h>
#include <intrin.h>
#include <fstream>
#include <stdlib.h>

class Hash
{
	public:

		std::string EncryptMessage(std::string message);
		std::string DecryptMessage(std::string cipher);

		int key = 9;
};

