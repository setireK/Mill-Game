#include "millmainwindow.h"
#include "ui_millmainwindow.h"
#include <QPalette>
#include <QPixmap>
#include <QIcon>
#include <QImage>
#include <QMessageBox>



MillMainWindow::MillMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MillMainWindow)
{
    ui->setupUi(this);
    _model = new Model();
    this->setFixedSize(650,700);
    //this->setStyleSheet("background-color: rgb(255,204,153);");
    this->setWindowTitle("Malom játék");
    connect(_model, &Model::NewGame, this, &MillMainWindow::OnModelNewGame);
    connect(_model, &Model::FieldChanged, this, &MillMainWindow::OnModelFieldChanged);
    connect(_model, &Model::StepHappend, this, &MillMainWindow::OnModelStepHappend);
    connect(_model, &Model::GameOver, this, &MillMainWindow::OnModelGameOver);

    _model->newGame();
}

void MillMainWindow::OnModelGameOver(int playerNum){
    if(playerNum == 0){
        QMessageBox::information(this, "Játék vége", "Gratulálunk a fehér játékosnak!");
    }
    else{
        QMessageBox::information(this, "Játék vége", "Gratulálunk a fekete játékosnak!");
    }
    _model->newGame();
}

void MillMainWindow::initTable(){
    for(int i= 0; i < 7; ++i){
        for(int j = 0; j < 7; ++j){
            auto pb = std::make_shared<QPushButton>();
            pb->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            connect(pb.get(), &QPushButton::clicked, this, &MillMainWindow::TableClicked);

            QString path = "../MillGame/Pictures/" + QString::number(i) + QString::number(j) + ".png";
            QIcon icon(path);

            pb->setIcon(icon);
            pb->setIconSize(QSize(pb->height()*3,pb->width()*3));
            _table.push_back(pb);

            static_cast<QGridLayout*>(ui->tableFrame->layout())->addWidget(pb.get(),i,j);
        }
    }
}

void MillMainWindow::OnModelStepHappend(int oldI, int oldJ, int newI, int newJ){
    //int oldIndex = oldI*7 + oldJ;
    //int newIndex = newI*7 + newJ;
    OnModelFieldChanged(oldI, oldJ);
    OnModelFieldChanged(newI, newJ);
}

void MillMainWindow::colorSwap(PlayerType p){
    QString color;
    QString backColor;
    switch (p) {
        case PlayerType::BLACK:
        color = "white";
        backColor = "black";
        break;
    case PlayerType::WHITE:
        color = "black";
        backColor = "white";
        break;
    default:
        break;
    }
    ui->label->setStyleSheet("color: " + color);
    ui->label_2->setStyleSheet("color: " + color);
    ui->label_3->setStyleSheet("color: " + color);
    ui->label_5->setStyleSheet("color: " + color);
    ui->remainingBlack->setStyleSheet("color: " + color);
    ui->remainingWhite->setStyleSheet("color: " + color);
    ui->takenBlack->setStyleSheet("color: " + color);
    ui->takenWhite->setStyleSheet("color: " + color);
    this->setStyleSheet("background-color: " + backColor);
}

void MillMainWindow::TableClicked(){
    QPushButton* sender = static_cast<QPushButton*>(QObject::sender());
    for(int i = 0; i < _table.length(); ++i){
        if(sender == _table[i].get()){
            int x = i / 7;
            int y = i % 7;
            _model->tableClicked(x,y);
            break;
        }
    }
}

void MillMainWindow::OnModelNewGame(Player p){
    _table.clear();
    switch(p.getPlayerType()){
        case PlayerType::BLACK:
            this->setStyleSheet("background-color: black");
        break;
        case PlayerType::WHITE:
            this->setStyleSheet("background-color: white");
        break;
        default:
        break;
    }
    colorSwap(p.getPlayerType());
    initTable();
}

void MillMainWindow::OnModelFieldChanged(int i, int j){
    int index = i*7 +j;
    QString path;
    switch(_model->getType(i,j)){
        case BLACK:
            path = "../MillGame/BlackPictures/" + QString::number(i) + QString::number(j) + ".png";
            break;
        case WHITE:
            path = "../MillGame/WhitePictures/" + QString::number(i) + QString::number(j) + ".png";
            break;
        case NEUTRAL:
            path = "../MillGame/Pictures/" + QString::number(i) + QString::number(j) + ".png";
        default:
            break;
    }
    QIcon icon(path);
    _table[index]->setIcon(icon);
    _table[index]->setIconSize(QSize(_table[index]->height()*3,_table[index]->width()*3));
    colorSwap(_model->getCurrentPlayerType());
    ui->remainingWhite->setText(QString::number((_model->getPlayers())[0]->getRemainingTokens()));
    ui->takenWhite->setText(QString::number((_model->getPlayers())[0]->getTakenTokens()));
    ui->remainingBlack->setText(QString::number((_model->getPlayers())[1]->getRemainingTokens()));
    ui->takenBlack->setText(QString::number((_model->getPlayers())[1]->getTakenTokens()));
}

MillMainWindow::~MillMainWindow()
{
    delete ui;
}

