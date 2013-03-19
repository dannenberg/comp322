all: tournament

tournament: Players.o RPSPlayer.o RPSTournament.o
	g++ Players.o RPSPlayer.o RPSTournament.o -o tournament

Players.o: Players.cc
	g++ -c Players.cc

RPSPlayer.o: RPSPlayer.cc
	g++ -c RPSPlayer.cc

RPSTournament.o: RPSTournament.cc
	g++ -c RPSTournament.cc

clean:
	rm -rf *.o tournament
