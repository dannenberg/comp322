#include "Players.h"

RockPlayer::RockPlayer(int x) {
    ostringstream oss;
    oss << "RockPlayer #" << x;
    name = oss.str();
}

RockPaperScissorChoice RockPlayer::chooseMove() {
    return ROCK;
}

PaperPlayer::PaperPlayer(int x) {
    ostringstream oss;
    oss << "PaperPlayer #" << x;
    name = oss.str();
}

RockPaperScissorChoice PaperPlayer::chooseMove() {
    return PAPER;
}

ScissorPlayer::ScissorPlayer(int x) {
    ostringstream oss;
    oss << "ScissorPlayer #" << x;
    name = oss.str();
}

RockPaperScissorChoice ScissorPlayer::chooseMove() {
    return SCISSOR;
}

RandomPlayer::RandomPlayer(int x) {
    ostringstream oss;
    oss << "RandomPlayer #" << x;
    name = oss.str();
}

RockPaperScissorChoice RandomPlayer::chooseMove() {
    return ROCK; // TODO make random
}
