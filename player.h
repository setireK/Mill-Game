#ifndef PLAYER_H
#define PLAYER_H

#include "playertype.h"


class Player
{
public:
    Player(PlayerType playerType);
    void tokenPlaced();
    void tokenRemoved() {_tokensOnField--;}
    void tokenTook() {_takenTokens++;}

    PlayerType getPlayerType() const {return _type;}
    int getTokensOnField() const {return _tokensOnField;}
    int getTakenTokens() const {return _takenTokens;}
    int getRemainingTokens() const{return _remainingTokens;}

private:

    int _remainingTokens;
    int _takenTokens;
    int _tokensOnField;
    PlayerType _type;
};

#endif // PLAYER_H
