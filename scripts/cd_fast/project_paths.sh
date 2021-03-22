#!/bin/sh

# Adjust this call to the correct python script
python scripts/project_paths.py --req_path $1
cd `cat ~/.repo_path`
#echo -n > $HOME/.repo_path
