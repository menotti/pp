#!/bin/bash
# source /opt/intel/inteloneapi/setvars.sh > /dev/null 2>&1

file=$1
/bin/echo "##" $(whoami) is about to execute ...
echo 
echo "Building script $file.."
mpirun -machinefile $PBS_NODEFILE ./$file


