import os
import platform

def clear_screen():
        if platform.system() == 'Windows':
            os.system('cls')
        else:
            os.system('clear')

def get_key() -> str:
        """키 입력 처리 (크로스 플랫폼)"""
        if platform.system() == 'Windows':
            import msvcrt
            key = msvcrt.getch()
            # Windows에서의 방향키 처리
            if key == b'\xe0':  # 특수키
                key = msvcrt.getch()
                if key == b'H': return 'UP'
                if key == b'P': return 'DOWN'
            elif key == b'\r': return 'ENTER'
            elif key == b'q': return 'QUIT'
        else:
            import sys, tty, termios
            fd = sys.stdin.fileno()
            old_settings = termios.tcgetattr(fd)
            try:
                tty.setraw(sys.stdin.fileno())
                ch = sys.stdin.read(1)
                if ch == '\x1b':
                    next1 = sys.stdin.read(1)
                    next2 = sys.stdin.read(1)
                    if next1 == '[':
                        if next2 == 'A': return 'UP'
                        if next2 == 'B': return 'DOWN'
                elif ch == '\n' or ch == '\r': return 'ENTER'
                elif ch == 'q': return 'QUIT'
            finally:
                termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
        return ''
    
