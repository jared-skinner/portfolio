'''
rmk.py

Perform a make clean and a make.  Standard out from "make clean" is suppressed.
The output of make is filtered for better readability.
'''

# python standard modules
import os
import subprocess

# my modules
import mk


def main():
    print("Performing make clean\n\n")
    FNULL = open(os.devnull, 'w')
    subprocess.call(["make.bat", "clean"], stdout=FNULL, stderr=subprocess.STDOUT)

    print("Performing a make\n\n")
    mk.main()


if __name__ == "__main__":
    main(args.c)
