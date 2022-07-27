all: RobustSSM

CFLAGS = -std=c++11 -O2

RobustSSM: RobustSSM.o Graph.o Functions.o
	$(CXX) $(CFLAGS) RobustSSM.o Graph.o Functions.o -o RobustSSM

RobustSSM.o: RobustSSM.cpp Graph.h ./include/clipp.h Graph.h
	$(CXX) $(CFLAGS) -c RobustSSM.cpp -o RobustSSM.o

Graph.o: Graph.cpp Graph.h
	$(CXX) $(CFLAGS) -c Graph.cpp -o Graph.o

Functions.o: Functions.cpp Functions.h Graph.h
	$(CXX) $(CFLAGS) -c Functions.cpp -o Functions.o

run: RobustSSM
	#./RobustSSM ./data/Video_game_network.txt ./data/Video_game_task.txt -tau 0
	#./RobustSSM ./data/Video_game_network.txt ./data/Video_game_task.txt -tau 0 -alg Frequency -result Frequency.txt
	./RobustSSM ./data/Video_game_network.txt ./data/Video_game_task.txt -tau 0 -alg OMegA -result OMegA.txt


clean:
	rm *.o
	rm RobustSSM