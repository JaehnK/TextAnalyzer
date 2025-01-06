#ifndef TEXTANALYZER_HPP
#define TEXTANALYZER_HPP

#include <iostream>
#include <vector>
#include <string>
#include <dirent.h>
#include <sys/stat.h>
#include <termios.h>
#include <unistd.h>
#include <algorithm>

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