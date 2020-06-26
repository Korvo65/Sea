#ifndef WORKER_H
#define WORKER_H

#include <QAbstractEventDispatcher>
#include <QObject>
#include <QThread>

class Worker : public QObject
{
    Q_OBJECT

public:
    explicit Worker(QObject *parent = 0)
        : QObject(parent)
    {}

signals:
    void sigStarted();
    void sigFinished();

public slots:
    void slotPause();
    void slotResume();
    void slotCancel();

protected:

    enum State { STOPPED, RUNNING, PAUSED };
    volatile State state = STOPPED;

    bool isCancelled() const;

};

#endif // WORKER_H
