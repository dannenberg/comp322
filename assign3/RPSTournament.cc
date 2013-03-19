#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

#include "RPSPlayer.h"
#include "Players.h"
using namespace std;

int main (void) {
    vector<RPSPlayer *> cur_round;
    vector<RPSPlayer *> next_round;
    RPSPlayer* cur = NULL;
    int round_num = 0;
    srand(time(NULL));
    cout << "Creating 128 players of assorted types." << endl;
    for (int i = 0; i < 128; i++) {
        int type = rand()%4;
        switch (type) {
            case 0:
                cur = new RockPlayer(i);
                break;
            case 1:
                cur = new PaperPlayer(i);
                break;
            case 2:
                cur = new ScissorPlayer(i);
                break;
            case 3:
                cur = new RandomPlayer(i);
                break;
        }
        cur_round.push_back(cur);
    }

    while (cur_round.size() > 1) { // tournament loop
        cout << "Starting round " << ++round_num << " with " << cur_round.size() << " players left." << endl;
        while (cur_round.size() > 0) { // round loop
            if (cur_round.size() == 1) { // odd number, so pass on the guy
                next_round.push_back(cur_round.front());
                break;
            }

            // pop the first two entries of the round and have them compete
            RPSPlayer* p1 = cur_round.front();
            cur_round.erase(cur_round.begin());
            RPSPlayer* p2 = cur_round.front();
            cur_round.erase(cur_round.begin());
            int ties = 0;

            RockPaperScissorChoice p1choice = p1->chooseMove();
            RockPaperScissorChoice p2choice = p2->chooseMove();
            Result result = RPSPlayer::evaluatePlay(p1choice, p2choice);
            p1->addRound(p1choice, p2choice);
            p2->addRound(p2choice, p1choice);

            while (ties < 3) {
                if (result == PLAYERONEWIN) { // p1 wins move him along
                    next_round.push_back(p1);
                    free(p2);
                    break;
                }
                else if (result == PLAYERTWOWIN) { // p2 wins move him along
                    next_round.push_back(p2);
                    free(p1);
                    break;
                }
                else { // tie
                    ties++;
                    p1choice = p1->chooseMove();
                    p2choice = p2->chooseMove();
                    result = RPSPlayer::evaluatePlay(p1choice, p2choice);
                    p1->addRound(p1choice, p2choice);
                    p2->addRound(p2choice, p1choice);
                }
            }
            if (ties >= 3) { // too many ties both must die
                free(p1);
                free(p2);
            }
        }
        cur_round.swap(next_round); // make next round current
        next_round.clear(); // empty next
    }
    if (cur_round.size() > 0) {
        RPSPlayer* winner = cur_round.front();
        cout << "We had a winner, " << winner->name << endl;
        cur_round.empty();
        free(winner);
    }
    else {
        cout << "There was a tie in the final round so there is no winnner" << endl;
    }
}
