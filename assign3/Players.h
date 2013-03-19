#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <sstream>

#include "RPSPlayer.h"
using namespace std;

class RockPlayer : public RPSPlayer::RPSPlayer {
    public:
        //always choose rock
        RockPlayer(int x);
        RockPaperScissorChoice chooseMove();
};

class PaperPlayer : public RPSPlayer::RPSPlayer {
    public:
        //always choose rock
        PaperPlayer(int x);
        RockPaperScissorChoice chooseMove();
};

class ScissorPlayer : public RPSPlayer::RPSPlayer {
    public:
        //always choose rock
        ScissorPlayer(int x);
        RockPaperScissorChoice chooseMove();
};

class RandomPlayer : public RPSPlayer::RPSPlayer {
    public:
        //always choose rock
        RandomPlayer(int x);
        RockPaperScissorChoice chooseMove();
};
