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
	#tau 0
#	./RobustSSM ./data/Video_game_network.txt ./data/Video_game_task.txt -tau 0
#	./RobustSSM ./data/Video_game_network.txt ./data/Video_game_task.txt -tau 0 -alg Frequency -result Frequency.txt
#	./RobustSSM ./data/Video_game_network.txt ./data/Video_game_task.txt -tau 0 -alg OMegA -result OMegA.txt
#
#	./RobustSSM ./data/wikispeedia_network.txt ./data/wikispeedia_task.txt -tau 0 -result wiki_Rose.txt
#	./RobustSSM ./data/wikispeedia_network.txt ./data/wikispeedia_task.txt -tau 0 -alg Frequency -result wiki_Frequency.txt
#	./RobustSSM ./data/wikispeedia_network.txt ./data/wikispeedia_task.txt -tau 0 -alg OMegA -result wiki_OMegA.txt

	#tau 1
	./RobustSSM ./data/Video_game_network.txt ./data/Video_game_task.txt -tau 0 -result Rose1.txt
	./RobustSSM ./data/Video_game_network.txt ./data/Video_game_task.txt -tau 0 -alg Frequency -result Frequency1.txt
	./RobustSSM ./data/Video_game_network.txt ./data/Video_game_task.txt -tau 0 -alg OMegA -result OMegA1.txt

	./RobustSSM ./data/wikispeedia_network.txt ./data/wikispeedia_task.txt -tau 0 -result wiki_Rose1.txt
	./RobustSSM ./data/wikispeedia_network.txt ./data/wikispeedia_task.txt -tau 0 -alg Frequency -result wiki_Frequency1.txt
	./RobustSSM ./data/wikispeedia_network.txt ./data/wikispeedia_task.txt -tau 0 -alg OMegA -result wiki_OMegA1.txt

	#tau 2
	./RobustSSM ./data/Video_game_network.txt ./data/Video_game_task.txt -tau 0 -result Rose2.txt
	./RobustSSM ./data/Video_game_network.txt ./data/Video_game_task.txt -tau 0 -alg Frequency -result Frequency2.txt
	./RobustSSM ./data/Video_game_network.txt ./data/Video_game_task.txt -tau 0 -alg OMegA -result OMegA2.txt

	./RobustSSM ./data/wikispeedia_network.txt ./data/wikispeedia_task.txt -tau 0 -result wiki_Rose2.txt
	./RobustSSM ./data/wikispeedia_network.txt ./data/wikispeedia_task.txt -tau 0 -alg Frequency -result wiki_Frequency2.txt
	./RobustSSM ./data/wikispeedia_network.txt ./data/wikispeedia_task.txt -tau 0 -alg OMegA -result wiki_OMegA2.txt

	#tau 3
	./RobustSSM ./data/Video_game_network.txt ./data/Video_game_task.txt -tau 0 -result Rose3.txt
	./RobustSSM ./data/Video_game_network.txt ./data/Video_game_task.txt -tau 0 -alg Frequency -result Frequency3.txt
	./RobustSSM ./data/Video_game_network.txt ./data/Video_game_task.txt -tau 0 -alg OMegA -result OMegA3.txt

	./RobustSSM ./data/wikispeedia_network.txt ./data/wikispeedia_task.txt -tau 0 -result wiki_Rose3.txt
	./RobustSSM ./data/wikispeedia_network.txt ./data/wikispeedia_task.txt -tau 0 -alg Frequency -result wiki_Frequency3.txt
	./RobustSSM ./data/wikispeedia_network.txt ./data/wikispeedia_task.txt -tau 0 -alg OMegA -result wiki_OMegA3.txt

	#tau 4
	./RobustSSM ./data/Video_game_network.txt ./data/Video_game_task.txt -tau 0 -result Rose4.txt
	./RobustSSM ./data/Video_game_network.txt ./data/Video_game_task.txt -tau 0 -alg Frequency -result Frequency4.txt
	./RobustSSM ./data/Video_game_network.txt ./data/Video_game_task.txt -tau 0 -alg OMegA -result OMegA4.txt

	./RobustSSM ./data/wikispeedia_network.txt ./data/wikispeedia_task.txt -tau 0 -result wiki_Rose4.txt
	./RobustSSM ./data/wikispeedia_network.txt ./data/wikispeedia_task.txt -tau 0 -alg Frequency -result wiki_Frequency4.txt
	./RobustSSM ./data/wikispeedia_network.txt ./data/wikispeedia_task.txt -tau 0 -alg OMegA -result wiki_OMegA4.txt

	#tau 5
	./RobustSSM ./data/Video_game_network.txt ./data/Video_game_task.txt -tau 0 -result Rose5.txt
	./RobustSSM ./data/Video_game_network.txt ./data/Video_game_task.txt -tau 0 -alg Frequency -result Frequency5.txt
	./RobustSSM ./data/Video_game_network.txt ./data/Video_game_task.txt -tau 0 -alg OMegA -result OMegA5.txt

	./RobustSSM ./data/wikispeedia_network.txt ./data/wikispeedia_task.txt -tau 0 -result wiki_Rose5.txt
	./RobustSSM ./data/wikispeedia_network.txt ./data/wikispeedia_task.txt -tau 0 -alg Frequency -result wiki_Frequency5.txt
	./RobustSSM ./data/wikispeedia_network.txt ./data/wikispeedia_task.txt -tau 0 -alg OMegA -result wiki_OMegA5.txt

clean:
	rm *.o
	rm RobustSSM