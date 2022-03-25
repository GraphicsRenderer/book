CCFLAGS=-Wall -Wextra -isystem ../../third_party -O2 -std=c++20

build: *.cpp
	g++ ${CCFLAGS} -o triangle-frame.exe triangle-frame.cpp
	g++ ${CCFLAGS} -o line-sweeping.exe line-sweeping.cpp
	g++ ${CCFLAGS} -o bbox.exe bbox.cpp

clean:
	rm -rf *.exe

.PHONY: clean
