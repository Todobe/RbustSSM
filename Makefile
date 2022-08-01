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
#	#tau 0
	./RobustSSM ./data/Video_game_network.txt ./data/Video_game_task.txt -tau -1 -result ./result3/Rose.txt -k 29
	./RobustSSM ./data/Video_game_network.txt ./data/Video_game_task.txt -tau -1 -alg Frequency -result ./result3/Frequency.txt -k 29
#	./RobustSSM ./data/Video_game_network.txt ./data/Video_game_task.txt -tau 0 -alg OMegA -result ./result/OMegA.txt -k 25
	./RobustSSM ./data/Video_game_network.txt ./data/Video_game_task.txt -tau -1 -alg Sequence -result ./result3/Sequence.txt -k 29
#
	./RobustSSM ./data/wikispeedia_network.txt ./data/wikispeedia_task.txt -tau -1 -result ./result3/wiki_Rose.txt -k 29
	./RobustSSM ./data/wikispeedia_network.txt ./data/wikispeedia_task.txt -tau -1 -alg Frequency -result ./result3/wiki_Frequency.txt -k 29
#	./RobustSSM ./data/wikispeedia_network.txt ./data/wikispeedia_task.txt -tau 0 -alg OMegA -result ./result/wiki_OMegA.txt
	./RobustSSM ./data/wikispeedia_network.txt ./data/wikispeedia_task.txt -tau -1 -alg Sequence -result ./result3/wiki_Sequence.txt -k 29
#
#	#tau 1
#	./RobustSSM ./data/Video_game_network.txt ./data/Video_game_task.txt -tau 1 -result ./result/Rose.txt -k 25
#	./RobustSSM ./data/Video_game_network.txt ./data/Video_game_task.txt -tau 1 -alg Frequency -result ./result/Frequency.txt -k 25
##	./RobustSSM ./data/Video_game_network.txt ./data/Video_game_task.txt -tau 1 -alg OMegA -result ./result/OMegA.txt
#	./RobustSSM ./data/Video_game_network.txt ./data/Video_game_task.txt -tau 1 -alg Sequence -result ./result/Sequence.txt -k 25
##
#	./RobustSSM ./data/wikispeedia_network.txt ./data/wikispeedia_task.txt -tau 1 -result ./result/wiki_Rose.txt -k 25
#	./RobustSSM ./data/wikispeedia_network.txt ./data/wikispeedia_task.txt -tau 1 -alg Frequency -result ./result/wiki_Frequency.txt -k 25
#	#./RobustSSM ./data/wikispeedia_network.txt ./data/wikispeedia_task.txt -tau 1 -alg OMegA -result ./result/wiki_OMegA.txt
#	./RobustSSM ./data/wikispeedia_network.txt ./data/wikispeedia_task.txt -tau 1 -alg Sequence -result ./result/wiki_Sequence.txt -k 25
##
##
##	#tau 2
#	./RobustSSM ./data/Video_game_network.txt ./data/Video_game_task.txt -tau 2 -result ./result/Rose.txt -k 25
#	./RobustSSM ./data/Video_game_network.txt ./data/Video_game_task.txt -tau 2 -alg Frequency -result ./result/Frequency.txt -k 25
##	./RobustSSM ./data/Video_game_network.txt ./data/Video_game_task.txt -tau 2 -alg OMegA -result ./result/OMegA.txt
#	./RobustSSM ./data/Video_game_network.txt ./data/Video_game_task.txt -tau 2 -alg Sequence -result ./result/Sequence.txt -k 25
##
#	./RobustSSM ./data/wikispeedia_network.txt ./data/wikispeedia_task.txt -tau 2 -result ./result/wiki_Rose.txt -k 25
#	./RobustSSM ./data/wikispeedia_network.txt ./data/wikispeedia_task.txt -tau 2 -alg Frequency -result ./result/wiki_Frequency.txt -k 25
##	./RobustSSM ./data/wikispeedia_network.txt ./data/wikispeedia_task.txt -tau 2 -alg OMegA -result ./result/wiki_OMegA.txt
#	./RobustSSM ./data/wikispeedia_network.txt ./data/wikispeedia_task.txt -tau 2 -alg Sequence -result ./result/wiki_Sequence.txt -k 25
##
##	#tau 3
#	./RobustSSM ./data/Video_game_network.txt ./data/Video_game_task.txt -tau 3 -result ./result/Rose.txt -k 25
#	./RobustSSM ./data/Video_game_network.txt ./data/Video_game_task.txt -tau 3 -alg Frequency -result ./result/Frequency.txt -k 25
##	./RobustSSM ./data/Video_game_network.txt ./data/Video_game_task.txt -tau 3 -alg OMegA -result ./result/OMegA.txt
#	./RobustSSM ./data/Video_game_network.txt ./data/Video_game_task.txt -tau 3 -alg Sequence -result ./result/Sequence.txt -k 25
#
#	./RobustSSM ./data/wikispeedia_network.txt ./data/wikispeedia_task.txt -tau 3 -result ./result/wiki_Rose.txt  -k 25
#	./RobustSSM ./data/wikispeedia_network.txt ./data/wikispeedia_task.txt -tau 3 -alg Frequency -result ./result/wiki_Frequency.txt  -k 25
##	./RobustSSM ./data/wikispeedia_network.txt ./data/wikispeedia_task.txt -tau 3 -alg OMegA -result ./result/wiki_OMegA.txt
#	./RobustSSM ./data/wikispeedia_network.txt ./data/wikispeedia_task.txt -tau 3 -alg Sequence -result ./result/wiki_Sequence.txt -k 25
#
#	#tau 4
#	./RobustSSM ./data/Video_game_network.txt ./data/Video_game_task.txt -tau 4 -result ./result/Rose.txt -k 25
#	./RobustSSM ./data/Video_game_network.txt ./data/Video_game_task.txt -tau 4 -alg Frequency -result ./result/Frequency.txt -k 25
##	./RobustSSM ./data/Video_game_network.txt ./data/Video_game_task.txt -tau 4 -alg OMegA -result ./result/OMegA.txt
#	./RobustSSM ./data/Video_game_network.txt ./data/Video_game_task.txt -tau 4 -alg Sequence -result ./result/Sequence.txt -k 25
##
#	./RobustSSM ./data/wikispeedia_network.txt ./data/wikispeedia_task.txt -tau 4 -result ./result/wiki_Rose.txt -k 25
#	./RobustSSM ./data/wikispeedia_network.txt ./data/wikispeedia_task.txt -tau 4 -alg Frequency -result ./result/wiki_Frequency.txt -k 25
##	./RobustSSM ./data/wikispeedia_network.txt ./data/wikispeedia_task.txt -tau 4 -alg OMegA -result ./result/wiki_OMegA.txt
#	./RobustSSM ./data/wikispeedia_network.txt ./data/wikispeedia_task.txt -tau 4 -alg Sequence -result ./result/wiki_Sequence.txt -k 25
##
##	#tau 5
#	./RobustSSM ./data/Video_game_network.txt ./data/Video_game_task.txt -tau 5 -result ./result/Rose.txt -k 25
#	./RobustSSM ./data/Video_game_network.txt ./data/Video_game_task.txt -tau 5 -alg Frequency -result ./result/Frequency.txt -k 25
##	./RobustSSM ./data/Video_game_network.txt ./data/Video_game_task.txt -tau 5 -alg OMegA -result ./result/OMegA.txt
#	./RobustSSM ./data/Video_game_network.txt ./data/Video_game_task.txt -tau 5 -alg Sequence -result ./result/Sequence.txt -k 25
##
#	./RobustSSM ./data/wikispeedia_network.txt ./data/wikispeedia_task.txt -tau 5 -result ./result/wiki_Rose.txt -k 25
#	./RobustSSM ./data/wikispeedia_network.txt ./data/wikispeedia_task.txt -tau 5 -alg Frequency -result ./result/wiki_Frequency.txt -k 25
##	./RobustSSM ./data/wikispeedia_network.txt ./data/wikispeedia_task.txt -tau 5 -alg OMegA -result ./result/wiki_OMegA.txt
#	./RobustSSM ./data/wikispeedia_network.txt ./data/wikispeedia_task.txt -tau 5 -alg Sequence -result ./result/wiki_Sequence.txt -k 25

clean:
	rm *.o
	rm RobustSSM