#include "TextAnalyzer.hpp"

// 키보드 입력을 위한 구조체
struct termios orig_termios;

// 터미널 설정을 raw 모드로 변경
void enableRawMode() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

// 터미널 설정을 원래대로 복구
void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

// 화면 지우기
void clearScreen() {
    std::cout << "\x1B[2J\x1B[H";
}

// 파일이 .txt로 끝나는지 확인
bool isTxtFile(const std::string& filename) {
    if (filename.length() < 4) return false;
    return filename.substr(filename.length() - 4) == ".txt";
}

// 디렉토리 내용 읽기 (.txt 파일만)
std::vector<std::string> readDirectory(const std::string& path = ".") {
    std::vector<std::string> files;
    DIR* dir = opendir(path.c_str());
    
    if (dir != nullptr) {
        struct dirent* entry;
        while ((entry = readdir(dir)) != nullptr) {
            std::string name = entry->d_name;
            // .txt 파일만 추가
            if (isTxtFile(name)) {
                files.push_back(name);
            }
        }
        closedir(dir);
    }
    
    std::sort(files.begin(), files.end());
    return files;
}

// 파일 목록 표시
void displayFiles(const std::vector<std::string>& files, int selectedIndex) {
    clearScreen();
    std::cout << "텍스트 파일(.txt) 선택 프로그램 (q: 종료, Enter: 선택)\n\n";
    
    if (files.empty()) {
        std::cout << "현재 디렉토리에 텍스트 파일이 없습니다." << std::endl;
        return;
    }
    
    for (size_t i = 0; i < files.size(); ++i) {
        if (i == static_cast<size_t>(selectedIndex)) {
            std::cout << "> " << files[i] << std::endl;
        } else {
            std::cout << "  " << files[i] << std::endl;
        }
    }
}

std::string SelectFile() {
    enableRawMode();
    
    std::vector<std::string> files = readDirectory();
    int selectedIndex = 0;
    bool running = true;
    std::string selectedFile;
    
    while (running && !files.empty()) {
        displayFiles(files, selectedIndex);
        
        char c;
        read(STDIN_FILENO, &c, 1);
        
        switch (c) {
            case 'A': // 위 화살표
                if (selectedIndex > 0) selectedIndex--;
                break;
            case 'B': // 아래 화살표
                if (selectedIndex < static_cast<int>(files.size()) - 1) selectedIndex++;
                break;
            case '\n': // Enter
                selectedFile = files[selectedIndex];
                running = false;
                break;
            case 'q': // 종료
                running = false;
                break;
        }
    }
    
    disableRawMode();
    clearScreen();
    
    if (!selectedFile.empty()) {
        std::cout << "선택된 파일: " << selectedFile << std::endl;
    }
    
    return selectedFile;
}