CCFLAGS=-I../../third_party -O2 -std=c++20

build: *.cpp
	g++ ${CCFLAGS} -o single-color.exe single-color.cpp
	g++ ${CCFLAGS} -o gradient-color.exe gradient-color.cpp

clean:
	rm -rf *.exe

.PHONY: clean
