CCFLAGS=-I../../third_party -O2 -std=c++20

build: *.cpp
	g++ ${CCFLAGS} -o line-0.01.exe line-0.01.cpp
	g++ ${CCFLAGS} -o line-pixel-space.exe line-pixel-space.cpp
	g++ ${CCFLAGS} -o bresenham.exe bresenham.cpp

clean:
	rm -rf *.exe

.PHONY: clean
