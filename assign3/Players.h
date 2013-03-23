#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <sstream>

#include "RPSPlayer.h"
using namespace std;

class RockPlayer : public RPSPlayer::RPSPlayer {
    public:
        // always choose rock
        RockPlayer(int x);
        RockPaperScissorChoice chooseMove();
};

class PaperPlayer : public RPSPlayer::RPSPlayer {
    public:
        // always choose paper
        PaperPlayer(int x);
        RockPaperScissorChoice chooseMove();
};

class ScissorPlayer : public RPSPlayer::RPSPlayer {
    public:
        // always choose scissor
        ScissorPlayer(int x);
        RockPaperScissorChoice chooseMove();
};

class RandomPlayer : public RPSPlayer::RPSPlayer {
    public:
        // choose at random
        RandomPlayer(int x);
        RockPaperScissorChoice chooseMove();
};

class CyclePlayer : public RPSPlayer::RPSPlayer {
    int a;
    public:
        // cycle choices
        CyclePlayer(int x);
        RockPaperScissorChoice chooseMove();
};

class BeatPreviousPlayer : public RPSPlayer::RPSPlayer {
    public:
        // beat previous opponentmove
        BeatPreviousPlayer(int x);
        RockPaperScissorChoice chooseMove();
};
