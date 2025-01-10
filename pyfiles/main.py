import os
import subprocess
import readfile
import SelectMethod
import PromptHandler as ph

def	ExecveCppProgram(input: str):
    process = subprocess.Popen(
        ['../WordFreqProg'],  # 컴파일된 C++ 프로그램
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True  # 문자열로 통신
    )
    
    try:
        # 입력 전달 및 결과 받기
        stdout, stderr = process.communicate(input=input, timeout=5)
        
        if process.returncode == 0:
            return stdout
        else:
            return f"Error: {stderr}"
            
    except subprocess.TimeoutExpired:
        process.kill()
        return "Error: Process timed out"
    except Exception as e:
        return f"Error: {str(e)}"


def main() -> int:
	flag = None
	while (flag != 'y'):
		method = SelectMethod.GetMethod()
		filename = readfile.GetFile()
		ph.clear_screen()	
		print(f"Method: {method}\nFile: {filename}")
		print("----" * 20)
		flag = input("Is it Correct? (y/n) ")
	#print(os.pwd())
	ExecveCppProgram(readfile.Openfile(filename))

if __name__ == "__main__":
    main()