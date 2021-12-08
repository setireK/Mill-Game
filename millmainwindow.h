#ifndef MILLMAINWINDOW_H
#define MILLMAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QVector>
#include "model.h"
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MillMainWindow; }
QT_END_NAMESPACE

class MillMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MillMainWindow(QWidget *parent = nullptr);
    ~MillMainWindow();

private:
    Ui::MillMainWindow *ui;
    Model* _model;
    QVector<std::shared_ptr<QPushButton>> _table;

    void colorSwap(PlayerType p);
    void initTable();
    void initTokens();
private slots:
    void OnModelNewGame(Player p);
    //void OnModelTableChanged();
    void OnModelFieldChanged(int i, int j);
    void OnModelStepHappend(int oldI, int oldJ, int newI, int newJ);
    void TableClicked();
    void OnModelGameOver(int playerNum);
};
#endif // MILLMAINWINDOW_H
