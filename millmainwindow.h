#ifndef MILLMAINWINDOW_H
#define MILLMAINWINDOW_H

#include <QMainWindow>
#include "model.h"

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

};
#endif // MILLMAINWINDOW_H
