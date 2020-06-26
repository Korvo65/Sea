#include "controllerwindow.h"
#include "ui_controllerwindow.h"

ControllerWindow::ControllerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ControllerWindow)
{
    ui->setupUi(this);
}

ControllerWindow::~ControllerWindow()
{
    delete ui;
}

void ControllerWindow::on_pushButton_clicked()
{
    emit sigPauseMathTask();
}

void ControllerWindow::on_pushButton_2_clicked()
{
    emit sigResumeMathTask();
}

void ControllerWindow::on_pushButton_3_clicked()
{
    emit sigCancelMathTask();
}
