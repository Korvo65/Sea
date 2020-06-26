#include "mathworker.h"

#include <math.h>
#include <QFile>
#include <QTextStream>

void MathWorker::doWork()
{
    if (state == PAUSED){
        state = RUNNING;
    }

    if (state == RUNNING){
        return;
    }

    state = RUNNING;
    emit sigStarted();

    // This loop simulates work
    bool directionRight = true;
    for(; state == RUNNING;){

        double curY = sin(x_);
        emit sigUpdateY(x_, curY);

        QThread::msleep(250);

        if (isCancelled()){
            break;
        }

        //Some logic for right/left moving x
        //Don't panic
        if(x_ >= 3.14) directionRight = false;
        if(x_ <= 0.) directionRight = true;
        directionRight ? (x_ += 0.1): (x_ -= 0.1);
    }

    saveXToFile();
    emit sigFinished();
}

void MathWorker::saveXToFile(){
    QFile file(".//data.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    out <<x_;
}
