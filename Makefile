all: build test run
build:
	g++ main.cpp -std=c++11 -O2 -o main.exe
test:
	for i in `seq -w 1 10` ; do ./main.exe < tests/test.$i.in > a ; if [[ "`diff a tests/test.$i.sol`" = "" ]] ; then echo "OK"; else echo "Failed $i" ; fi ; done
run:
	./main.exe
