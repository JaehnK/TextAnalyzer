#ifndef TEXTANALYZER_HPP
#define TEXTANALYZER_HPP

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>

#ifdef _WIN32
    #include <windows.h>
    #include <io.h>
    #include <fcntl.h>
#else
    #include <dirent.h>
    #include <sys/stat.h>
    #include <termios.h>
    #include <unistd.h>
    #include <locale>
    #include <codecvt>
#endif

#include "KoreanTextReader.hpp"

class	WordFreq
{
	private:
		std::wstring	word;
		int				freq;
	
	public:
		WordFreq();
		~WordFreq();

		WordFreq(WordFreq &wf);
		WordFreq operator = (const WordFreq& wf);

};

std::string SelectFile();

#endif