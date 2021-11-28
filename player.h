#ifndef PLAYER_H
#define PLAYER_H

#include "playertype.h"


class Player
{
public:
    Player(PlayerType playerType);

    void tokenPlaced();
private:
    int _remainingTokens;
    int _tokensOnField;
    PlayerType _type;
};

#endif // PLAYER_H
