#ifndef MODEL_H
#define MODEL_H

#include <QVector>
#include <QObject>
#include <QMap>
#include <QString>
#include "player.h"


class Model : QObject
{
    Q_OBJECT
public:
    Model();

    void placeToken(int x, int y);
    void moveToken(int x, int y);

private:
    void initTable();

    PlayerType _table[7][7];
    Player* _players[2];

signals:
    void GameOver();

};

#endif // MODEL_H
