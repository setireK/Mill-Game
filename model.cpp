#include "model.h"
#include <QRandomGenerator64>

Model::Model()
{
}

bool Model::allMill() const {
    int counter = 0;
    for(int i = 0; i < 7; ++i){
        for(int j = 0; j < 7; ++j){
            if(_table[i][j] == _otherPlayer->getPlayerType() && isMill(i,j)){
                ++counter;
            }
        }
    }
    if(counter == _otherPlayer->getTokensOnField()){
        return true;
    }
    return false;
}

void Model::tableClicked(int i, int j){
    if(_table[i][j] == NONE || _table[i][j] == ORIGO){
        return;
    }
    switch(_currentState){
    case GameState::PLACE:
        if(_table[i][j] == NEUTRAL && _currentPlayer->getRemainingTokens() > 0){
            _table[i][j] = _currentPlayer->getPlayerType();
            _currentPlayer->tokenPlaced();
            if(isMill(i,j) && !allMill()){
                _currentState = GameState::TAKE;
                emit FieldChanged(i,j);
                break;
            }
            else{
                stepPlayer();
                if(_players[0]->getRemainingTokens() == 0 && _players[1]->getRemainingTokens() == 0){
                    _currentState = GameState::STEP;
                }
            }
        }
        emit FieldChanged(i,j);
        break;
    case GameState::TAKE:
            if(!isMill(i,j) && _table[i][j] != _currentPlayer->getPlayerType() && _table[i][j] != NEUTRAL && _table[i][j] != NONE && _table[i][j] != ORIGO){
                _table[i][j] = NEUTRAL;
                _currentPlayer->tokenTook();
                stepPlayer();
                _currentPlayer->tokenRemoved();
                if(!checkGameOver()){
                    if(_currentPlayer->getRemainingTokens() == 0){
                        _currentState = GameState::STEP;
                    }
                    else{
                        _currentState = GameState::PLACE;
                    }
                }
                emit FieldChanged(i,j);
            }
        break;
    case GameState::STEP:
        if(_selectedNode == NONE){
            if(_table[i][j] == _currentPlayer->getPlayerType())
            {
                _selectedNode = _table[i][j];
                _selected_i = i;
                _selected_j = j;
            }
        }
        else{
            if(_table[i][j] == _currentPlayer->getPlayerType()){
                _selectedNode = _table[i][j];
                _selected_i = i;
                _selected_j = j;
            }
            if(_currentPlayer->getTokensOnField() > 3){
                if(neighbors(_selected_i,_selected_j, i ,j) && _table[i][j] == NEUTRAL){
                    _table[i][j] = _selectedNode;
                    _table[_selected_i][_selected_j] = NEUTRAL;
                    emit StepHappend(_selected_i, _selected_j, i, j);
                    _selected_i = -1;
                    _selected_j = -1;
                    _selectedNode = NONE;
                    if(isMill(i,j) && !allMill()){
                        _currentState = GameState::TAKE;
                    }
                    else{
                        stepPlayer();
                    }
                }
            }
            else{
                if(_table[i][j] == NEUTRAL){
                    _table[i][j] = _selectedNode;
                    _table[_selected_i][_selected_j] = NEUTRAL;
                    emit StepHappend(_selected_i, _selected_j, i, j);
                    _selected_i = -1;
                    _selected_j = -1;
                    _selectedNode = NONE;
                    if(isMill(i,j) && !allMill()){
                        _currentState = GameState::TAKE;

                    }
                    else{
                        stepPlayer();
                    }

                }
            }
        }
        emit FieldChanged(i,j);
        break;
    }
}

bool Model::neighbors(int firstI,int firstJ, int secondI, int secondJ){
    if(firstI == secondI && firstJ == secondJ){
        return false;
    }
    int fromI;
    int toI;
    int fromJ;
    int toJ;
    if(firstI <= secondI){
        fromI = firstI;
        toI = secondI;
    }
    else{
        fromI = secondI;
        toI = firstI;
    }
    if(firstJ <= secondJ){
        fromJ = firstJ;
        toJ = secondJ;
    }
    else{
        fromJ = secondJ;
        toJ = firstJ;
    }
    if(firstI != secondI && firstJ != secondJ){
        return false;
    }
    else if(firstI == secondI){
        for(int j = fromJ+1; j <= toJ; j++){
            if(_table[firstI][j] != NONE){
                if(toJ == j){
                    return true;
                }
                return false;
            }
        }
        return false;
    }
    else if(firstJ == secondJ){
        for(int i = fromI+1; i <= toI; i++){
            if(_table[i][firstJ] != NONE){
                if(toI == i){
                    return true;
                }
                return false;
            }
        }
        return false;
    }
    else{
        return false;
    }
}

void Model::generateCurrentPlayer(){
    int numberOfShuffle = QRandomGenerator::global()->bounded(0,2);
    if(numberOfShuffle == 0){
        _currentPlayer = _players[0];
        _otherPlayer = _players[1];
    }
    else{
        _currentPlayer = _players[1];
        _otherPlayer = _players[0];
    }
}

void Model::newGame(){
    _players[0] = new Player(WHITE);
    _players[1] = new Player(BLACK);
    initTable();
    generateCurrentPlayer();
    _currentState = GameState::PLACE;
    _selectedNode = NONE;
    emit NewGame(*_currentPlayer);
}

void Model::initTable(){
    for(int i = 0; i < 7; ++i){
        for(int j = 0; j < 7; ++j){
            if(i == 3 && j == 3){
                _table[i][j] = ORIGO;
            }
            else if(i == j || j == 3 || j == 6-i || i == 3){
                _table[i][j] = NEUTRAL;
            }
            else{
                _table[i][j] = NONE;
            }
        }
    }
}

bool Model::isMill(int x, int y) const{
    if(milledRow(x,y) || milledColumn(x,y)){
        return true;
    }
    return false;
}

bool Model::milledRow(int x, int y) const{
    if(x == 3){
        if(y < 3){
            return checkRows(0,3,x);
        }
        else{
            return checkRows(4,7,x);
        }
    }
    else{
        return checkRows(0,7,x);
    }
}


bool Model::milledColumn(int x,int y) const{
    if(y == 3){
        if(x < 3){
            return checkCols(0,3,y);
        }
        else{
            return checkCols(4,7,y);
        }
    }
    else{
        return checkCols(0,7,y);
    }
}

bool Model::checkRows(int from, int to, int row) const{
    int millCounter = 0;
    for(int i = from; i < to; i++){
        if(_table[row][i] != NONE){
            if(_table[row][i] == BLACK){
                millCounter++;
            }
            else if(_table[row][i] == WHITE){
                millCounter--;
            }
        }
    }
    if(millCounter == 3 || millCounter == -3){
        return true;
    }
    return false;
}

bool Model::checkCols(int from, int to, int col) const{
    int millCounter = 0;
    for(int i = from; i < to; i++){
        if(_table[i][col] != NONE){
            if(_table[i][col] == BLACK){
                millCounter++;
            }
            else if(_table[i][col] == WHITE){
                millCounter--;
            }
        }
    }
    if(millCounter == 3 || millCounter == -3){
        return true;
    }
    return false;
}


bool Model::checkGameOver() const{
    if(_players[0]->getTokensOnField() < 3 && _players[0]->getRemainingTokens() == 0){
        emit GameOver(1);
        return true;
    }
    else if(_players[1]->getTokensOnField() < 3 && _players[1]->getRemainingTokens() == 0){
        emit GameOver(0);
        return true;
    }
    return false;
}

void Model::stepToken(int currX, int currY, int nextX, int nextY){
    if(_table[nextX][nextY] == NEUTRAL){
        if(_currentPlayer->getPlayerType() == _table[currX][currY]){
            _table[nextX][nextY] = _table[currX][currY];
            _table[currX][currY] = NEUTRAL;
        }
    }
}

void Model::placeToken(int x, int y){
    if(_table[x][y] == NEUTRAL){
        if(_currentPlayer->getPlayerType() == BLACK){
            _table[x][y] = BLACK;
        }
        else{
            _table[x][y] = WHITE;
        }
        _currentPlayer->tokenPlaced();
        stepPlayer();
        emit FieldChanged(x,y);
    }
}

void Model::removeToken(int x, int y){
    switch (_currentPlayer->getPlayerType()) {
        case BLACK:
            if(_table[x][y] == WHITE && !isMill(x,y)){
                _table[x][y] = NEUTRAL;
                _players[0]->tokenRemoved();
                checkGameOver();
                stepPlayer();
            }
        break;
        case WHITE:
            if(_table[x][y] == BLACK && !isMill(x,y)){
                _table[x][y] = NEUTRAL;
                _players[1]->tokenRemoved();
                checkGameOver();
                stepPlayer();
            }
        break;
        default:
        break;
    }
}

void Model::stepPlayer(){
    if(_currentPlayer->getPlayerType() == BLACK){
        _currentPlayer = _players[0];
        _otherPlayer = _players[1];
    }
    else{
        _currentPlayer = _players[1];
        _otherPlayer = _players[0];
    }
}
