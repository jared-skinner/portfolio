import argparse
import mk
import os
import subprocess


def main(noclp = False):

    print("Performing make clean\n\n")
    FNULL = open(os.devnull, 'w')
    if noclp:
        subprocess.call(["make.bat", "noclp", "clean"], stdout=FNULL, stderr=subprocess.STDOUT)
    else:
        subprocess.call(["make.bat", "clean"], stdout=FNULL, stderr=subprocess.STDOUT)

    print("Performing a make\n\n")
    mk.main()


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='rmk', prog="rmk.py")
    parser.add_argument('-v', '--version', action='version', version='%(prog)s 0.0.1.0')
    parser.add_argument('-c', help='pass noclp argument to make clean', action="store_true")
    args = parser.parse_args()

    main(args.c)
