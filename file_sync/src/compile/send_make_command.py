"""
This is one of two scripts which work together to allow controlling the compile
process from a linux VM to windows.  This script creates a file contining the
compile command and the destination directory.  This file is then picked up by
A script sitting on the host machine which runs the specified compile command in
the given directory.
"""

import sys 
import re
import os
import argparse
import smartdest

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='filesync', prog="filesync.py")
    parser.add_argument('-v', '--version', action='version', version='%(prog)s 0.0.1.0')
    parser.add_argument('-f', help='File name')
    parser.add_argument('-a', help='Action')
    args = parser.parse_args()

    if(args.f):
        #find dest file
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
        targetdir = 'D:/osi/' + config + '/'

    targetdir = targetdir + 'monarch/src/' + r.group(2).lower() + '/'

    with open("/home/jared/D/scripts/autocompile/command", 'w') as command_file:
            command_file.write(args.a + "\r\n" + targetdir)

