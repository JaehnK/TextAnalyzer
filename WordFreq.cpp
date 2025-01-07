#include "TextAnalyzer.hpp"

std::unordered_map<std::string, int>	WordFreq(std::vector<std::string> output)
{
	std::unordered_map<std::string, int> freq;
	std::stringstream ss;
    std::string word;
    
    for (const auto& sentence : output)
    {
        ss.clear();
        ss.str(sentence);
        
        // 문장을 공백 기준으로 단어로 분리
        while (ss >> word)
        {
            freq[word]++;
        }
	}
	return (freq);
}

void SaveFreqToCsv(const std::unordered_map<std::string, int>& freq, const std::string& filename)
{
    std::vector<std::pair<std::string, int>> vec;
    for (const auto& pair : freq)
	{
        vec.push_back(pair);
    }
    
    std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b)
		{  
            return a.second > b.second;  // 빈도수 내림차순
        });
    
    // 파일 열기 (차이점 4: string을 직접 전달 가능)
    std::ofstream out(filename);  // C++11에서는 .c_str() 불필요
    if (!out.is_open()) {
        std::cerr << "파일을 열 수 없습니다: " << filename << std::endl;
        return;
    }
    
    // 헤더 작성
    out << "단어,빈도수\n";
    
    // 데이터 작성 (차이점 5: range-based for loop)
    for (const auto& pair : vec) {
        out << pair.first << "," << pair.second << "\n";
    }
}