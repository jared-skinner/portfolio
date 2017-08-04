'''
send_make_command.py

This is one of two scripts which work together to allow controlling the compile
process from a linux VM to windows.  This script creates a file contining the
compile command and the destination directory.  This file is then picked up by
A script sitting on the host machine (see "autocompile.py") which runs the
specified compile command in the given directory.

In order to use this script, dest.fs needs to be configured in the project.
dest.fs contains information on where compilation should take place.
'''

# python standard modules
import sys 
import re
import os
import argparse

# my modules
import smartdest


def main():
    parser = argparse.ArgumentParser(description='filesync', prog="filesync.py")
    parser.add_argument('-v', '--version', action='version', version='%(prog)s 0.0.1.0')
    parser.add_argument('-f', help='File name.  Used for determining the root of the current project')
    parser.add_argument('-a', help='Action to send')
    args = parser.parse_args()

    # Find dest file.
    if(args.f):
        #All projects I care about start with the word "Open", so use this for
        #matching.
        r = re.search("(.*)(Open[A-Za-z]+)(/.*?/)", args.f)
        if r:
            file_path = r.group(1) + r.group(2) + r.group(3)

        dest_file = file_path + "dest.fs"

    if not os.path.isfile(dest_file):
        print("dest.fs does not exist.  Please configure before using")
        exit()

    config_file = open(dest_file, 'r')
    config_file = config_file.read().splitlines()
    config = config_file[0]

    # get the destination environment
    if config == "auto":
        #use auto matching to determine which directory to copy to
        targetdir = smart_dest.smart_dest(dest_file)
        r = re.search("/home/jared/D/(.*)", targetdir)
        if r:
            targetdir = "D:/" + r.group(1)
    else:
        targetdir = 'D:/environment/' + config + '/'

    targetdir = targetdir + '/src/' + r.group(2).lower() + '/'

    with open("/home/jared/D/scripts/autocompile/command", 'w') as command_file:
            command_file.write(args.a + "\r\n" + targetdir)


if __name__ == "__main__":
    main()
