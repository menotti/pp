#!/bin/bash
# source /opt/intel/inteloneapi/setvars.sh > /dev/null 2>&1

file=$1
/bin/echo "##" $(whoami) is compiling ...
echo 
echo "Building script $file.."
mpiicpc -cxx=icc $file.c -o $file -diag-disable=10441
if [ -f "$file" ]; then 
    echo "Script $file built !";
    rm $file.c;
else 
    echo "Fail, script $file not built!";
fi

