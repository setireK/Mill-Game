#ifndef MODEL_H
#define MODEL_H

#include <QVector>
#include <QObject>
#include <QMap>
#include <QString>
#include "player.h"


class Model : public QObject
{
    Q_OBJECT
public:
    Model();
    enum class GameState{PLACE, TAKE, STEP};
    void placeToken(int x, int y);
    void moveToken(int x, int y);
    void removeToken(int x, int y);
    void stepToken(int currX, int currY, int nextX, int nextY);
    void newGame();
    void tableClicked(int x, int y);
    PlayerType getType(int x, int y) const {return _table[x][y];}
    PlayerType getCurrentPlayerType() const {return _currentPlayer->getPlayerType();}
    auto getPlayers() const {return _players;}

private:
    void initTable();
    bool isMill(int x, int y) const;
    void stepPlayer();
    bool checkGameOver() const;
    bool milledRow(int x, int y) const;
    bool milledColumn(int x,int y) const;
    bool checkRows(int from, int to, int col) const;
    bool checkCols(int from, int to, int row) const;
    void generateCurrentPlayer();
    bool neighbors(int firstI,int firstJ, int secondI, int secondJ);
    bool allMill() const;

    PlayerType _table[7][7];
    Player* _players[2];
    Player* _currentPlayer;
    Player* _otherPlayer;
    GameState _currentState;
    PlayerType _selectedNode;
    int _selected_i;
    int _selected_j;


signals:
    void GameOver(int player) const;
    void GameStarted(int player);
    void TableChanged();
    void FieldChanged(int i, int j);
    void StepHappend(int oldI, int oldJ, int newI, int newJ);
    void NewGame(Player currPlayer);
};

#endif // MODEL_H
