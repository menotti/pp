# precisamos modificar o CMAkeLists para adicionar um novo target: "run-profile"

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++17 -fsycl")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")

add_executable(mandelbrot main.cpp)
target_link_libraries(mandelbrot OpenCL sycl)
add_custom_target(run ./mandelbrot)

add_executable(mandelbrot_usm main.cpp)
target_compile_definitions(mandelbrot_usm PRIVATE MANDELBROT_USM)
target_link_libraries(mandelbrot_usm OpenCL sycl)
add_custom_target(run_usm ./mandelbrot_usm)

add_custom_target(run-profile
  COMMAND advisor --collect=roofline --project-dir=./adv -- ./mandelbrot_usm
  COMMAND advisor --report=roofline --project-dir=./adv --report-output=./../../mandel_roofline.html
  DEPENDS mandelbrot_usm
  COMMENT "Running Intel Advisor on MandelBrot_USM"
)
