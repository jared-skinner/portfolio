'''
mk.py

This script is designed to call a make.bat script on windows which uses Visual
Studio's C compiler and linker.  The scrip will then filter the output,
displaying info, warnings and errors in a much easier to read fashion.
'''

from termcolor import colored
from terminaltables import DoubleTable
import subprocess
import re

def execute(cmd):
    '''
    Call cmd and use a generator expression to filter and yield each line of
    standard out produced by the command
    '''

    popen = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, universal_newlines=True)

    # use regular expressions to determin message type and filter accordingly
    for stdout_line in iter(popen.stdout.readline, ""):
        stdout_line = re.sub(r'^\s+cl.*', "", stdout_line)

        stdout_line = re.sub(r'(^\w+\.c$|^\w+\.cpp$)', colored("\nCOMPILING   ", "green")+" \\1", stdout_line)
        stdout_line = re.sub(r'^\s*[a-zA-Z\\\_0-9:\.]*\.cp*', "", stdout_line)
        stdout_line = re.sub(r'^\s*[a-zA-Z\\\_0-9:\.]*\\', "", stdout_line)

        stdout_line = re.sub(r'^\s+link .*(\b\w+\.exe).*', colored("LINKING      ", "green")+"\\1", stdout_line)

        stdout_line = re.sub(r'^\s+LIB.*(\b\w+\.lib).*', colored("CREATING LIB ", "green")+"\\1", stdout_line)

        stdout_line = re.sub(r'Generating Code...\n', "", stdout_line)

        stdout_line = re.sub(r'^LINK .*\n', "", stdout_line)

        stdout_line = re.sub("warning\s*(U|C|LNK)(\d+)", colored("warning \\1\\2", "yellow"), stdout_line)
        stdout_line = re.sub("fatal error\s*(LNK|U)(\d+)", colored("fatal error \\1\\2", "red"), stdout_line)
        stdout_line = re.sub("error\s*(C|LNK)(\d+)", colored("error   \\1\\2", "red"), stdout_line)

        stdout_line = re.sub("^\(\s*(.*?)\)\s*:", "\\1" + ":", stdout_line)

        stdout_list = stdout_line.split(": ")

        # In the case of a warning or error message, pad results if some portion
        # of the message is missing.  This can happen on occasion...
        if len(stdout_list) == 2:
            stdout_list.insert(1, "")
            stdout_list.insert(2, "")

        if len(stdout_list) == 3:
            stdout_list.insert(2, "")

        if len(stdout_list) == 4:
            yield stdout_list
        else:
            yield stdout_line 

    popen.stdout.close()
    return_code = popen.wait()

    if return_code:
        print("Process exited with return code " + str(return_code))


def main():

    table_data = []

    for line in execute(["make.bat"]):
        # if type of line is an error or warning message
        if type(line) is str:
            if table_data != []:
                table_data.insert(0, ["Line Number", "Type", "Location", "Message"])
                table = DoubleTable(table_data)
                print(table.table)
                table_data = []
                print("")

            print(line, end="")
        else:
            # get rid of newline in message string
            line[3] = re.sub("\n", "", line[3])
            table_data.append(line)


if __name__ == "__main__":
    main()
