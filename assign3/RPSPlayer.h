#ifndef RPSPLAYER_H
#define RPSPLAYER_H
#include <vector>
#include <string>
using namespace std;

//enum to represent a move choice. This allows headers in the below functions to
//take as input RockPaperScissorChoice instead of an int, which
//could lead to confusion since there are more than 3 ints.
enum RockPaperScissorChoice { ROCK, PAPER, SCISSOR };

//enum to represent result from a round
enum Result { PLAYERONEWIN, PLAYERTWOWIN, TIE};

class RPSPlayer {
protected:
  vector<RockPaperScissorChoice> myMoves;
  vector<RockPaperScissorChoice> myOpponentMoves;

public:
  //virtual function that should be overridden in inheriting classes
  virtual RockPaperScissorChoice chooseMove() = 0;

  // used to print player names
  string name;

  //stores the results of a move into myMoves and myOpponentMoves. This information *could*
  //be used by chooseMove() or it could be ignored.
  void addRound(RockPaperScissorChoice myMove, RockPaperScissorChoice opponentMove);

  //This method should return a Result enum representing whether p1 won (PLAYERONEWIN), p2 won (PLAYERTWOWIN), or a tie (TIE)
  static Result evaluatePlay(RockPaperScissorChoice p1, RockPaperScissorChoice p2);
};
#endif
