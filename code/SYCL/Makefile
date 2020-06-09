CXX = dpcpp
CXXFLAGS = -O2 -g
LDFLAGS = -lOpenCL -lsycl
EXE_NAME = main
SOURCES = main.cpp

all: main

main:
	$(CXX) $(CXXFLAGS) -o $(EXE_NAME) $(SOURCES) $(LDFLAGS)

run: 
	./$(EXE_NAME)

clean: 
	rm -rf $(EXE_NAME)
