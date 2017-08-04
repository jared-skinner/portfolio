"""
filesync.py

Copy files from an repo directory to an full environment.  This script ties in
nicely to vim's plugin neomake which will call this script every time a file
saves.  This script will copy an entire OpenNet copy over to an environment, or
just a single file.
"""

import shutil
from distutils import dir_util
import re
import os
import argparse


def copytree(src, dst, symlinks=False, ignore=None):
    """
    Copy the whole OpenNet folder

    Keyword arguments:
    src      -- the directory we want to copy from
    dst      -- the directory we want to copy to
    syslinks -- if true, preserve symlinks.  if false, copy symlink contents
    ignore   -- ignore specified directories

    returns: none
    """

    for item in os.listdir(src):
        s = os.path.join(src, item)
        d = os.path.join(dst, item)
        if os.path.isdir(s):
            shutil.copytree(s, d, symlinks, ignore)
        else:
            shutil.copy2(s, d)


def can_copy_to_dest():
    """
    Determine if we are able to copy to the specified destination.  If a
    different OpenNet copy has been copied over to the dest, prompt the user on
    whether or not it is ok to copy.

    returns: bool
    """

    # get src directory
    r = re.search(".*?(Prod1|Prod2|Prod3)/(.*?)/", dest_file)
    print(dest_file)
    if r:
        directory = r.group(2)
        print(r.group(2))

    # check src_file
    src_file_path = targetdir + 'src.fs'
    if os.path.isfile(src_file_path):
        src_file = open(src_file_path, 'r')
        src = src_file.read().splitlines()
        if src:
            src = src[0]

        if not src == directory:
            print("The last file sync to this destination used a different source.  Would you like to continue? y/n")
            answer = ""
            while answer is not "y":
                answer = input()
                if answer is "n":
                    return False
                if answer is "y":
                    src_file.close()

                    #delete src file
                    os.remove(targetdir + 'src.fs')

                    src_file = open(src_file_path, "w")
                    src_file.write(directory)
                    src_file.close()
                    return True

                print("valid answers are \"y\" and \"n\"")
    else:
        #TODO: do a product, path in the src_file so we can write from multiple
        # projects without having to switch
        src_file = open(src_file_path, 'w')
        src_file.write(directory)
        src_file.close()
        return True


def main():
    parser = argparse.ArgumentParser(description='filesync', prog="filesync.py")
    parser.add_argument('-v', '--version', action='version', version='%(prog)s 0.0.1.0')
    parser.add_argument('-f', help='Sync single file, by default all files are copied')
    parser.add_argument('--dest_file', help='Absolute path to the destination file.  This is required')
    args = parser.parse_args()

    if args.f:
        r = re.search("(.*Prod1/.*?/)", args.f)
        if r:
            dest_file = r.group(1) + "/dest.fs"
        else:
            r = re.search("(.*Open[a-zA-Z]+/.*?/)", args.f)
            if r:
                dest_file = r.group(1) + "dest.fs"
    else:
        dest_file = args.dest_file

    try:
        config_file = open(dest_file, 'r')
        config_file = config_file.read().splitlines()
        config = config_file[0]
    except FileNotFoundError:
        print("dest.fs does not exist.  Please configure before using")
        exit()


    if config == "auto":
        #use auto matching to determine which directory to copy to
        targetdir = smart_dest.smart_dest(dest_file)
    else:
        targetdir = '/home/jared/D/osi/' + config + '/'

    # check if targetdir exists.  If not complain and exit
    if not os.path.isdir(targetdir):
        print(targetdir)
        print("Environment provided in dest.fs does not exist.  Check configuration and try again")
        exit()

    # check is src.fs exists in dest, if so make sure we are allowed to copy from this directory
    if not args.f:
        can_copy_to_dest()

    if args.f:
        #file path

        r = re.search(".*Prod1/.*?/(.*)", args.f)
        if r:
            file_path = r.group(1)
            target = targetdir + file_path
        else:
            r = re.search(".*Open[a-zA-Z]+/.*?/(.*)", args.f)
            if r:
                file_path = r.group(1)
                target = targetdir + file_path

        print("src: " + args.f)
        print("target: " + target)
        shutil.copy(args.f, target)
        print("copy complete!")
    else:
        #src path
        r = re.search("(.*Prod1/.*?/)", dest_file)
        if r:
            src_path = r.group(1)
        else:
            r = re.search("(.*Open[a-zA-Z]+/.*?/)", dest_file)
            if r:
                src_path = r.group(1)

        print("src: " + src_path)
        print("target: " + targetdir)
        dir_util.copy_tree(src_path, targetdir)
        print("copy complete!")


if __name__ == '__main__':
    main()

