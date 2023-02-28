
source /opt/intel/inteloneapi/setvars.sh > /dev/null 2>&1s
# Advisor env-variables
source /opt/intel/inteloneapi/advisor/2023.0.0/advisor-vars.sh
source /opt/intel/inteloneapi/advisor/2023.0.0/advixe-vars.sh

#Build by CMAKE
mkdir build
cd build
cmake ..
make

make run-profile
