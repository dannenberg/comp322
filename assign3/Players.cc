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
    int choice = rand()%3;
    switch (choice) {
        case 0:
            return ROCK;
        case 1:
            return PAPER;
        case 2:
            return SCISSOR;
        default: // cant occur, but to be safe...
            return ROCK;
    }
}

CyclePlayer::CyclePlayer(int x) {
    ostringstream oss;
    oss << "CyclePlayer #" << x;
    name = oss.str();
}

RockPaperScissorChoice CyclePlayer::chooseMove() {
    a++;
    switch (a%3) {
        case 0:
            return ROCK;
        case 1:
            return PAPER;
        case 2:
            return SCISSOR;
        default: // cant occur, but to be safe...
            return ROCK;
    }
}

BeatPreviousPlayer::BeatPreviousPlayer(int x) {
    ostringstream oss;
    oss << "BeatPreviousPlayer #" << x;
    name = oss.str();
}

RockPaperScissorChoice BeatPreviousPlayer::chooseMove() {
    if (myOpponentMoves.size() > 0) {
        switch (myOpponentMoves.back()) {
            case SCISSOR:
                return ROCK;
            case ROCK:
                return PAPER;
            case PAPER:
                return SCISSOR;
        }
    }
    else { // if no previous moves, do random
        int choice = rand()%3;
        switch (choice) {
            case 0:
                return ROCK;
            case 1:
                return PAPER;
            case 2:
                return SCISSOR;
            default: // cant occur, but to be safe...
                return ROCK;
        }
    }
}
