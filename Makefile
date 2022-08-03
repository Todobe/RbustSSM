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
	mkdir result
#	#tau 0
	./RobustSSM ./data/Video_game_network.txt ./data/Video_game_task.txt -tau -1 -result ./result/Rose.txt -k 29
	./RobustSSM ./data/Video_game_network.txt ./data/Video_game_task.txt -tau -1 -alg Frequency -result ./result/Frequency.txt -k 29
	./RobustSSM ./data/Video_game_network.txt ./data/Video_game_task.txt -tau 0 -alg OMegA -result ./result4/OMegA.txt -k 29
	./RobustSSM ./data/Video_game_network.txt ./data/Video_game_task.txt -tau -1 -alg check -result ./result/OMegA.txt -k 29 -o omega.txt
	./RobustSSM ./data/Video_game_network.txt ./data/Video_game_task.txt -tau -1 -alg Sequence -result ./result6/Sequence.txt -k 29
#
	./RobustSSM ./data/wikispeedia_network.txt ./data/wikispeedia_task.txt -tau -1 -result ./result/wiki_Rose.txt -k 29
	./RobustSSM ./data/wikispeedia_network.txt ./data/wikispeedia_task.txt -tau -1 -alg Frequency -result ./result6/wiki_Frequency.txt -k 29
	./RobustSSM ./data/wikispeedia_network.txt ./data/wikispeedia_task.txt -tau 0 -alg OMegA -k 29 -o wiki_omega.txt
	./RobustSSM ./data/wikispeedia_network.txt ./data/wikispeedia_task.txt -tau -1 -alg check -result ./result/wiki_OMegA.txt -k 29 -o wiki_omega.txt
	./RobustSSM ./data/wikispeedia_network.txt ./data/wikispeedia_task.txt -tau -1 -alg Sequence -result ./result/wiki_Sequence.txt -k 29

clean:
	rm *.o
	rm RobustSSM