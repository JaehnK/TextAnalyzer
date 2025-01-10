from typing import List, Optional
from enum import Enum

import PromptHandler as ph

class MethodSelector:
	def	__init__(self):
		self.method = ["형태소 분석", "단어 빈도 분석", "Word2Vec"]
		self.selected_index: int = 0

	def DisplayMethods(self) -> None:
			ph.clear_screen()
			print("분석 기법 선택 (q: 종료, Enter: 선택)\n")
			for idx, file in enumerate(self.method):
				if idx == self.selected_index:
					print(f"> {file}")
				else:
					print(f"  {file}")

	def SelectMethod(self) -> Optional[str]:
			while True:
				self.DisplayMethods()
				key = ph.get_key()
				
				if key == 'UP' and self.selected_index > 0:
					self.selected_index -= 1
				elif key == 'DOWN' and self.selected_index < len(self.method) - 1:
					self.selected_index += 1
				elif key == 'ENTER':
					return self.method[self.selected_index]
				elif key == 'QUIT':
					return None

def GetMethod() -> str:
    m = MethodSelector()
    return (m.SelectMethod())