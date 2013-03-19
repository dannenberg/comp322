#include "Players.h"

RockPlayer::RockPlayer(int x) {
    player_num = x;
}

string RockPlayer::getName() {
    return "RockPlayer #" + player_num;
}

RockPaperScissorChoice RockPlayer::chooseMove() {
    return ROCK;
}

PaperPlayer::PaperPlayer(int x) {
    player_num = x;
}

string PaperPlayer::getName() {
    return "PaperPlayer #" + player_num;
}

RockPaperScissorChoice PaperPlayer::chooseMove() {
    return PAPER;
}

ScissorPlayer::ScissorPlayer(int x) {
    player_num = x;
}

string ScissorPlayer::getName() {
    return "ScissorPlayer #" + player_num;
}

RockPaperScissorChoice ScissorPlayer::chooseMove() {
    return SCISSOR;
}

RandomPlayer::RandomPlayer(int x) {
    player_num = x;
}

string RandomPlayer::getName() {
    return "RandomPlayer #" + player_num;
}

RockPaperScissorChoice RandomPlayer::chooseMove() {
    return ROCK; // TODO make random
}
