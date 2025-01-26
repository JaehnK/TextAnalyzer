import os
from typing import List, Optional
import platform

import PromptHandler as ph

class FileSelector:
	def __init__(self):
		self.files: List[str] = []
		self.selected_index: int = 0

	def is_txt_file(self, filename: str) -> bool:
		return filename.endswith('.txt')

	def read_directory(self, path: str = ".") -> List[str]:
		files = []
		for file in os.listdir(path):
			if self.is_txt_file(file):
				files.append(file)
		return sorted(files)

	def display_files(self) -> None:
		ph.clear_screen()
		print("텍스트 파일(.txt) 선택 프로그램 (q: 종료, Enter: 선택)\n")
		for idx, file in enumerate(self.files):
			if idx == self.selected_index:
				print(f"> {file}")
			else:
				print(f"  {file}")

	def select_file(self) -> Optional[str]:
		self.files = self.read_directory()
		if not self.files:
			print("현재 디렉토리에 텍스트 파일이 없습니다.")
			return

		while True:
			self.display_files()
			key = ph.get_key()
			
			if key == 'UP' and self.selected_index > 0:
				self.selected_index -= 1
			elif key == 'DOWN' and self.selected_index < len(self.files) - 1:
				self.selected_index += 1
			elif key == 'ENTER':
				return self.files[self.selected_index]
			elif key == 'QUIT':
				return None

def GetFile() -> str:
	print("File selector started")
	selector = FileSelector()
	selected_file = selector.select_file()
	if (selected_file):
		return (selected_file)
	else:
		print("현재 디렉토리에 텍스트 파일이 없습니다.")
		return (None)

def Openfile(filename: str) -> str:
	with open(file=filename, mode='r') as f:
		content = f.read()
	print(content)
	return (content)