"""
" Paths.py is a script that parse current project_name PWD path, and return the requested path fromm its repository
"
" CMI:
"    project_name_paths.pu <src, simics, core, uncore, testmodel, unittest, targets, regression>
"
" 
"
"
"""

import argparse
import sys
import os

# Set project name to variable
project_name = "X"

# Fill up the project repository structure
project_repo = { "root" : "/..",
             project_name : "",
             "src" : "/src",
             "include" : "/include",
             "hw" : "/hw",
             "simics" : "/simics",
             "core" : "/simics/CoreDevice",
             "uncore" : "/simics/UncoreDevice",
             "base" : "/simics/BaseDevice",
             "regression" : "/regression",
             "testmodel" : "/regression/test_model",
             "tests" : "/regression/test_model/tests",
             "unittests" : "/regression/test_model/unit_tests",
             "cfg" : "/regression/test_model/cfg",
             "targets" : "/regression/test_model/targets"}

def run(req_path):

    # Open output file which will hold the final path for linux usage
    home = os.environ['HOME']
    ofile = home + "/.repo_path"
    f = open(ofile, 'w')
  
    pwd = os.getcwd()

    repo  = pwd.split("/")
    if project_name in repo:
        project_version = project_name
    elif (project_name + "_v1") in repo:
        project_version = project_name + "_v1"
    else:
        f.write("")
        print("ERROR: Not under " + project_name + " repo directory...")
        sys.exit(0)

    root = ''
    for project_folder in repo:
        if project_folder == project_version:
            break
        else:  
            root = root +  "/" + project_folder

    path =  root + '/' + project_version + project_repo[req_path]

    f.write(path)
    f.close


def parse(path):

    match = [i for i in project_repo if path in i]

    if not match:
        print("ERROR: Not a valid " + project_name + " repo path...")
        sys.exit(0)
    
    return match

    

def main():
    global args
    parser = argparse.ArgumentParser(description='Get requested path fromm ' + \
            project_name + ' repo directory')
    parser.add_argument("--req_path", type=str,
                        help=('Requested path to return from project repo directory\n'
                            + 'Options: rsc, hw, include, core, uncore, base, regression'
                            + 'testmodel, unittest, test, targets'),
                        default='')
    
    args = parser.parse_args()
    if not args.req_path:
        print("ERROR: Missing --req_path argument...")
        sys.exit(0)

    req_path = parse(args.req_path)

    run(req_path[0])




if __name__=="__main__":
    main()
