#!/bin/sh

python $PPC/home/dmv_home/scripts/project_paths.py --req_path $1
cd `cat ~/.repo_path`
#echo -n > $HOME/.repo_path
