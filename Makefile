all: demoSoA demoAoS

demoSoA: demoSoA.cc ArrayView.hh ArrayView.o
	g++ -o demoSoA --std=c++17 ArrayView.o demoSoA.cc

demoAoS: demoAoS.cc ArrayView.hh ArrayView.o
	g++ -o demoAoS --std=c++17 ArrayView.o demoAoS.cc

ArrayView.o:  ArrayView.cc ArrayView.hh
	g++ -c --std=c++17 ArrayView.cc

clean:
	rm demoSoA demoAoS ArrayView.o
