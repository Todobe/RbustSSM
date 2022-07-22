all: RobustSSM

CFLAGS = -std=c++11

RobustSSM: RobustSSM.o graph.o
	$(CXX) $(CFLAGS) RobustSSM.o graph.o -o RobustSSM

RobustSSM.o: RobustSSM.cpp graph.h ./include/clipp.h ./graph.h
	$(CXX) $(CFLAGS) -c RobustSSM.cpp -o RobustSSM.o

graph.o: graph.cpp graph.h
	$(CXX) $(CFLAGS) -c graph.cpp -o graph.o

run: RobustSSM
	./RobustSSM ./data/Video_game_network.txt ./data/Video_game_task.txt

clean:
	rm *.o
	rm RobustSSM