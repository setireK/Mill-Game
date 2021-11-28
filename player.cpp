#include "player.h"
#include <stdexcept>

Player::Player(PlayerType playerType)
{
    if(playerType != BLACK && playerType != WHITE){
        throw std::invalid_argument("Player MUST be BLACK or WHITE");
    }
    _type = playerType;
    _remainingTokens = 9;
}

void Player::tokenPlaced(){
    if(_remainingTokens == 0 || _tokensOnField == 9){
        throw std::logic_error("No tokens left");
    }
    _remainingTokens--;
    _tokensOnField++;
}
