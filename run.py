import subprocess
import shlex
from pathlib import Path

def sh(command, echo=True):
    print("\x1b[7m> "+command+"\x1b[0m")
    p = subprocess.run(shlex.split(command), shell=True)

if __name__ == '__main__':    
    sh("./target/Debug/SimpleApp.exe")
