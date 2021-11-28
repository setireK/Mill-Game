#include "model.h"

Model::Model()
{
    _players[0] = new Player(WHITE);
    _players[1] = new Player(BLACK);
    initTable();
}

void Model::initTable(){
    for(int i = 0; i < 7; ++i){
        for(int j = 0; j < 7; ++j){
            if(i == 3 && j == 3){
                _table[i][j] = NONE;
            }
            else if(i == j || j == 3 || j == 6-i || i == 3){
                _table[i][j] = NEUTRAL;
            }
            else{
                _table[i][j] = NONE;
            }
        }
        if(i == 6){
            int x = 69;
        }
    }
}
