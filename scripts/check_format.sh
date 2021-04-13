#!/bin/bash
#
# CI pipeline help script to check correct format from HEAD commit from
# previous commit (HEAD~1)
#
# Usage: 
# Run script within the repository as it depends on `git` and the `clang-format`
# plugin embedded

DIFF=`git clang-format --diff HEAD~1 HEAD`

NO_CHANGES="no modified files to format"

if [ ! -z "$DIFF" ] && [ "$DIFF" != "$NO_CHANGES" ]
then
  echo "$DIFF"
  echo "FAILED"
  exit 1
fi

echo "$NO_CHANGES"
exit 0
