#include <string>
#include "RPSPlayer.h"
using namespace std;

class RockPlayer : public RPSPlayer::RPSPlayer {
    public:
        //always choose rock
        RockPlayer(int x);
        string getName();
        RockPaperScissorChoice chooseMove();
};

class PaperPlayer : public RPSPlayer::RPSPlayer {
    public:
        //always choose rock
        PaperPlayer(int x);
        string getName();
        RockPaperScissorChoice chooseMove();
};

class ScissorPlayer : public RPSPlayer::RPSPlayer {
    public:
        //always choose rock
        ScissorPlayer(int x);
        string getName();
        RockPaperScissorChoice chooseMove();
};

class RandomPlayer : public RPSPlayer::RPSPlayer {
    public:
        //always choose rock
        RandomPlayer(int x);
        string getName();
        RockPaperScissorChoice chooseMove();
};
