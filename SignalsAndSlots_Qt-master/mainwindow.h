#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mathworker.h"
#include "graphicwindow.h"
#include "controllerwindow.h"
#include <QFile>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
      void showEvent(QShowEvent *ev) override;
      void closeEvent (QCloseEvent *event) override;

private:
      double readXFromFile(QString path);
      void slotSaveXToFile(double x_);

signals:
      void sigShowEvent();
      void sigCloseEvent();

private slots:
      void slotShowEvent();
      void slotUpdateY(double x, double y);

private:
    Ui::MainWindow *ui;
    GraphicWindow *graphicWindow;
    ControllerWindow *controllerWindow;
    QThread *mathFuncWorkerThread;
    MathWorker *mathWorker;
};

#endif // MAINWINDOW_H
