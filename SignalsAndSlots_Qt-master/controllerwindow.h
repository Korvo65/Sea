#ifndef CONTROLLERWINDOW_H
#define CONTROLLERWINDOW_H

#include <QMainWindow>

namespace Ui {
class ControllerWindow;
}

class ControllerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ControllerWindow(QWidget *parent = 0);
    ~ControllerWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

signals:
    void sigPauseMathTask();
    void sigResumeMathTask();
    void sigCancelMathTask();

private:
    Ui::ControllerWindow *ui;
};

#endif // CONTROLLERWINDOW_H
