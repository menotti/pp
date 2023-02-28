# precisamos modificar o CMAkeLists para adicionar um novo target: "run-profile"

if(PERF_NUM)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -g -fsycl -std=c++17 -D PERF_NUM")
message (STATUS "target will be built for performance tabulation")
else()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsycl -std=c++17")
endif()
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")
add_executable (dct DCT.cpp)
target_link_libraries(dct OpenCL sycl)
file(COPY ../res/willyriver.bmp DESTINATION .)
add_custom_target (run ./dct willyriver.bmp willyriver_processed.bmp)

add_custom_target(run-profile
  COMMAND advisor --collect=roofline --project-dir=./adv --  ./dct willyriver.bmp willyriver_processed.bmp
  COMMAND advisor --report=roofline --project-dir=./adv --report-output=./../../../dct_roofline.html
  DEPENDS dct
  COMMENT "Running Intel Advisor on dct")
