'''
autocompile.py

This script continuously listens for "request" to compile.  Requests are
submitted by modifying the file titled "command".  This script is designed to be
used in conjunction with another script (see "send_make_command.py") tied in to
your favorite text editor).  Note, this script does not use locking of any kind.
This could result in race conditions.

The request come in two parts:

    1. Compile destination

        The folder where compilation should take place.

    2. Compile command

        The command to send to use for building.

            make   - perform "make"

            remake - perform "make clean && make"
'''


# python standard modules
import os
import argparse
import time

# my modules
import mk
import rmk


def readCompileCommand():
    '''
    Read in command file and clear contents for next cycle
    '''

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
    '''
    execute command pulled from "command" file
    '''

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
    '''
    read "command" file and compile software from now till the end of time
    '''

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
