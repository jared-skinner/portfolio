import sys 
import shutil
import distutils
from distutils import dir_util
import re
import os
import argparse
import subprocess
import time

import mk
import rmk


def readCompileCommand():
    # check if compile file exists
    if not os.path.isfile('command'):
        return False

    # read contents
    with open('command', 'r+') as command_file:
        compile = command_file.read().splitlines()

        # clear contents
        command_file.seek(0)
        command_file.write("")
        command_file.truncate()

    if (compile):
        return compile
    else:
        return False


def executeCommand(compile_dest, compile_command):
    os.chdir(compile_dest)
    # call make
    if compile_command == "make":
        print("Compiling in " + compile_dest)
        mk.main()

    if compile_command == "remake":

        print("Recompiling in " + compile_dest)
        rmk.main()

    os.chdir('D:/scripts/autocompile')


def main():
    while True:
        time.sleep(1)

        compile = readCompileCommand()

        if not compile:
            continue

        executeCommand(compile[1], compile[0])


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Compile automatically in windows on save in linux', prog="autocompile.py")
    parser.add_argument('-v', '--version', action='version', version='%(prog)s 0.0.1.0')
    args = parser.parse_args()

    main()

