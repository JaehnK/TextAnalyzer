#include "KoreanTextReader.hpp"
#include "TextAnalyzer.hpp"

bool KoreanTextReader::openFile(const std::string& filename)
{
    file.imbue(std::locale("ko_KR.UTF-8"));  // UTF-8 로케일 설정
    file.open(filename);
    
    if (!file.is_open()) {
        std::cerr << "파일을 열 수 없습니다: " << filename << std::endl;
        return false;
    }
    return true;
}

std::string KoreanTextReader::readLine()
{
    std::wstring wline;
    if (std::getline(file, wline)) {
        try {
            return converter.to_bytes(wline);
        } catch(const std::exception& e) {
            std::cerr << "변환 오류: " << e.what() << std::endl;
            return "";
        }
    }
    return "";
}

std::vector<std::string> KoreanTextReader::readAllLines() {
    std::vector<std::string> lines;
    std::string line;
    while (!(line = readLine()).empty()) {
        lines.push_back(line);
    }
    return lines;
}

void KoreanTextReader::closeFile() {
    if (file.is_open()) {
        file.close();
    }
}

KoreanTextReader::~KoreanTextReader() {
    closeFile();
}