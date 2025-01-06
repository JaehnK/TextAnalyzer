#include "TextAnalyzer.hpp"

bool hasUTF8BOM(const std::string& data) {
    return (data.size() >= 3 && 
            (unsigned char)data[0] == 0xEF &&
            (unsigned char)data[1] == 0xBB &&
            (unsigned char)data[2] == 0xBF);
}

std::wstring OpenFile(const std::string& path) {
    // 파일을 바이너리 모드로 읽기
    std::ifstream file(path, std::ios::binary);
    if (!file) {
        return L"";
    }

    // 전체 파일 내용을 string으로 읽기
    std::string content((std::istreambuf_iterator<char>(file)), 
                        std::istreambuf_iterator<char>());
    file.close();

    // BOM 체크 및 제거
    if (hasUTF8BOM(content)) {
        content = content.substr(3);
    }

#ifdef _WIN32
    try {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        return converter.from_bytes(content);
    } catch (...) {
        return L"";
    }
#else
    std::wstring result;
    
    try {
        // wifstream으로 직접 읽기 시도
        std::wifstream wif(path);
        wif.imbue(std::locale("ko_KR.UTF-8"));
        
        if (wif.is_open()) {
            std::wstringstream wss;
            wss << wif.rdbuf();
            result = wss.str();
            wif.close();
        }

        // 결과가 비어있거나 읽기 실패한 경우 변환 시도
        if (result.empty()) {
            std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
            result = converter.from_bytes(content);
        }
        
    } catch (...) {
        try {
            // 수동 UTF-8 디코딩 시도
            result.reserve(content.size());
            
            for (size_t i = 0; i < content.size();) {
                if ((content[i] & 0x80) == 0) {
                    // ASCII 문자
                    result.push_back(static_cast<wchar_t>(content[i]));
                    i++;
                }
                else if ((content[i] & 0xE0) == 0xC0 && i + 1 < content.size()) {
                    // 2바이트 UTF-8
                    wchar_t ch = ((content[i] & 0x1F) << 6) |
                                (content[i + 1] & 0x3F);
                    result.push_back(ch);
                    i += 2;
                }
                else if ((content[i] & 0xF0) == 0xE0 && i + 2 < content.size()) {
                    // 3바이트 UTF-8 (한글 포함)
                    wchar_t ch = ((content[i] & 0x0F) << 12) |
                                ((content[i + 1] & 0x3F) << 6) |
                                (content[i + 2] & 0x3F);
                    result.push_back(ch);
                    i += 3;
                }
                else {
                    // 잘못된 UTF-8 시퀀스는 건너뜀
                    i++;
                }
            }
        } catch (...) {
            return L"";
        }
    }
    
    return result;
#endif
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

int	main(void)
{
	std::string FileName = SelectFile();
	// std::wstring str = OpenFile(FileName);
	
	// if (str.empty())
	// {
	// 	std::cerr << "TextAnalyzer: Invalid or Empty File" << std::endl;
	// 	return (1);
	// }
	// else
	// 	std::wcout << str << std::endl;
	

    KoreanTextReader reader;
    reader.openFile(FileName);
    std::vector<std::string> output = reader.readAllLines();
    
    for (std::vector<std::string>::size_type i = 0; i < output.size(); i++)
    { 
        std::cout << "vec 의 " << i + 1 << " 번째 원소 :: " << output[i] << std::endl;
    }
	return (0);
}