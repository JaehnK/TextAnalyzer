#include "TextAnalyzer.hpp"

bool hasUTF8BOM(const std::string& data) {
    return (data.size() >= 3 && 
            (unsigned char)data[0] == 0xEF &&
            (unsigned char)data[1] == 0xBB &&
            (unsigned char)data[2] == 0xBF);
}

void initConsole()
{
	#ifdef _WIN32
		SetConsoleOutputCP(CP_UTF8);
		SetConsoleCP(CP_UTF8);
	#else
		std::locale::global(std::locale("ko_KR.UTF-8"));
		setlocale(LC_ALL, "ko_KR.UTF-8");
	#endif
}

//int	main(void)
//{
//	std::string 		FileName = SelectFile();
//	KoreanTextReader	reader;
//    reader.openFile(FileName);
//    std::vector<std::string>	output	=	reader.readAllLines();
//    std::unordered_map			freq	=	WordFreq(output);
//	SaveFreqToCsv(freq, "Freq.csv");
//	return (0);
//}

int	main(void)
{
	std::vector <std::string>	lines;
	std::string 				line;

	while (std::getline(std::cin, line))
	{
		lines.push_back(line);
	}

	std::unordered_map			freq	=	WordFreq(lines);
	SaveFreqToCsv(freq, "Freq.csv");
	
	return (0);
}