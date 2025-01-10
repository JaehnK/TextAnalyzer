#ifndef TEXTANALYZER_HPP
#define TEXTANALYZER_HPP

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <unordered_map>

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

std::string 							SelectFile();
std::unordered_map<std::string, int>	WordFreq(std::vector<std::string> output);
void 									SaveFreqToCsv(const std::unordered_map<std::string, int>& freq, const std::string& filename);

#endif