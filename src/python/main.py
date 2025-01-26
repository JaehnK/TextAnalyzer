import os
import subprocess
import sys
sys.path.append('..')

import readfile
import SelectMethod
import PromptHandler as ph
import WordFreqAnalyzer

def main() -> int:
	flag = None
	while (flag != 'y'):
		method = SelectMethod.GetMethod()
		filename = readfile.GetFile()
		ph.clear_screen()
		print(f"Method: {method}\nFile: {filename}")
		print("----" * 20)
		flag = input("Is it Correct? (y/n) ")
	with open(filename, 'rb') as f:
		file = f.read()
	text = file.decode('utf-8')
	freq = WordFreqAnalyzer.analyze_freq([text])
	WordFreqAnalyzer.save_to_csv(freq)

if __name__ == "__main__":
    main()