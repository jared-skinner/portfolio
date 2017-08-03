import re

def smart_dest(dest_file):
    '''Uses the version of OpenNet specified in dest_file to find the closest
    matching environment.  Environments are named OpenNet_x.x.x.x.  The x.x.x.x 
    is what smart_dest looks for.  Matches are done left to right, rounding up.
    
    Keyword arguments:
    dest_file -- the file containing the version of OpenNet to match against

    Returns: string
    '''

    #get version number
    r = re.search("(?<=v).*(?=dev)", dest_file).group(0)

    #turn into array
    versions = r.split("_")

    #get all environment directories
    dirs = next(os.walk('/home/jared/D/osi'))[1]

    dirs_temp = []

    #build candidate array (only grab things of the form "OpenNet_)"
    for dir in dirs:
        r = re.search("(?<=OpenNet_).*", dir)
        if r != None:
                dirs_temp.append(r.group(0))

    dirs = dirs_temp

    i = 0
    #do matching against the version number
    for version in versions:
        dirs_temp = []
        dirs_temp = check_version(version, dirs, i)

        i += 1

        if dirs_temp == []:
                break

        dirs = dirs_temp

    # if we still have more than one candidate, grab the environment of the last
    # version checked
    max = 0
    if len(dirs) > 1:
        choice = ""
        for dir in dirs:
            ver = dir.split('.')[i - 1]
            if int(ver) > max:
                max = int(ver)
                choice = dir
    else:
        choice = dirs[0]

    targetdir = "/home/jared/D/osi/OpenNet_" + choice + "/"

    return targetdir
