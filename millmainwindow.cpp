#include "millmainwindow.h"
#include "ui_millmainwindow.h"



MillMainWindow::MillMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MillMainWindow)
{
    ui->setupUi(this);
    _model = new Model();

}

MillMainWindow::~MillMainWindow()
{
    delete ui;
}

