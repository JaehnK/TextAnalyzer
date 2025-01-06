#ifndef KOREAN_TEXT_READER_H
#define KOREAN_TEXT_READER_H

#include "TextAnalyzer.hpp"
class KoreanTextReader
{
    private:
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        std::wifstream file;

    public:
        // 파일 열기
        bool openFile(const std::string& filename);

        // 한 줄씩 읽기
        std::string readLine();

        // 전체 파일 읽기
        std::vector<std::string> readAllLines();

        // 파일 닫기
        void closeFile();

        // 소멸자
        ~KoreanTextReader();
};

#endif