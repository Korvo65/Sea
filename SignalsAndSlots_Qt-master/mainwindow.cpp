#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graphicwindow.h"

#include <QThread>
#include <QString>
#include <QTextStream>
#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    graphicWindow = new GraphicWindow(this);
    graphicWindow->setWindowTitle("Graphic Wisualisation");
    controllerWindow = new ControllerWindow(this);
    controllerWindow->setWindowTitle("Contolls");

    //connect on Window Show Event
    connect(this, SIGNAL(sigShowEvent()), this, SLOT(slotShowEvent()));
}

void MainWindow::showEvent(QShowEvent *ev)
{
    QMainWindow::showEvent(ev);
    emit sigShowEvent();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    sigCloseEvent();
    //this timeout needs because main thread kill mathWorkerThread before mathWorkerThread exit safe
    QThread::msleep(200);
    QMainWindow::closeEvent(event);
}

void MainWindow::slotShowEvent()
{
    mathFuncWorkerThread = new QThread(this);
    mathWorker = new MathWorker(readXFromFile(".//data.txt"));
    mathWorker->moveToThread(mathFuncWorkerThread);

    connect(mathFuncWorkerThread, &QThread::started, mathWorker, &MathWorker::doWork);
    //QObject in mathWorker should be deleted by deleteLater according to documentation
    connect(mathWorker, &MathWorker::sigFinished, mathWorker, &QObject::deleteLater);
    connect(mathFuncWorkerThread, &QThread::finished, mathFuncWorkerThread, &QObject::deleteLater);
    connect(mathWorker, &QObject::destroyed, mathFuncWorkerThread, &QThread::quit);
    //if mathFuncWorkerThread stops, user want to quit, because of that - next connection
    connect(mathFuncWorkerThread, &QThread::finished, this, &QApplication::quit);

    //connecting 'EditText' With Event 'sigUpdateY'
    connect(mathWorker, &MathWorker::sigUpdateY, this, &MainWindow::slotUpdateY);
    //connecting 'Graphic' With Event 'sigUpdateY'
    connect(mathWorker, &MathWorker::sigUpdateY, graphicWindow, &GraphicWindow::slotRewriteGraph);

    //connecting controller events
    connect(controllerWindow, &ControllerWindow::sigPauseMathTask, mathWorker, &MathWorker::slotPause);
    connect(controllerWindow, &ControllerWindow::sigResumeMathTask, mathWorker, &MathWorker::slotResume);
    connect(controllerWindow, &ControllerWindow::sigCancelMathTask, mathWorker, &MathWorker::slotCancel);
    connect(this, &MainWindow::sigCloseEvent, mathWorker, &MathWorker::slotCancel);

    mathFuncWorkerThread->start();
    graphicWindow->show();
    controllerWindow->show();
}

void MainWindow::slotUpdateY(double x, double y)
{
    ui->textEdit->setText(ui->textEdit->toPlainText() +
                          "sin(" + QString::number(x) + ") = " +
                          QString::number(y) +
                          QString("\n") );
}

double MainWindow::readXFromFile(QString path){
    double x;

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return 0.;

    QTextStream in(&file);
    QString line = in.readLine();
    if (!line.isNull()) {
        bool ok = false;
        x = line.toDouble(&ok);

        if((ok == false) || (x < 0.) || (x > 4.))
            return 0.;
    }

    return x;
}

MainWindow::~MainWindow()
{
    //!!! mathWorker shouldn't be deleted directly
    //! "Deleting a QObject while pending events are waiting to be delivered can cause a crash.
    //! You must not delete the QObject directly if it exists in a different thread than the one currently executing.
    //! Use deleteLater() instead, which will cause the event loop to delete the object after all pending events have been delivered to it."

    delete graphicWindow;
    delete controllerWindow;
    delete ui;
}
