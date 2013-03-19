#include "RPSPlayer.h"

//This method should return a Result enum representing whether p1 won (PLAYERONEWIN), p2 won (PLAYERTWOWIN), or a tie (TIE)
Result RPSPlayer::evaluatePlay(RockPaperScissorChoice p1, RockPaperScissorChoice p2) {
    if (p1 == p2)
        return TIE;
    switch (p1) { // this is clear but not as concise as it could be
        case ROCK:
            if (p2 == SCISSOR)
                return PLAYERONEWIN;
            else
                return PLAYERTWOWIN;
        case PAPER:
            if (p2 == ROCK)
                return PLAYERONEWIN;
            else
                return PLAYERTWOWIN;
        case SCISSOR:
            if (p2 == PAPER)
                return PLAYERONEWIN;
            else
                return PLAYERTWOWIN;
    }
}

void RPSPlayer::addRound(RockPaperScissorChoice myMove, RockPaperScissorChoice opponentMove) {
    myMoves.push_back(myMove);
    myOpponentMoves.push_back(opponentMove);
}
