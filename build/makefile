all:
	g++ -c -g -o Layer.o ../lib/Layer.cpp
	g++ -c -g -o Neuron.o ../lib/Neuron.cpp
	g++ -c -g -o Net.o ../lib/Net.cpp
	g++ -c -g -o main.o ../lib/main.cpp
	g++ -o executible main.o Net.o Neuron.o Layer.o
	rm *.o

