#ifndef MATHWORKER_H
#define MATHWORKER_H

#include "worker.h"

class MathWorker : public Worker
{
    Q_OBJECT

public:
    explicit MathWorker(double x = 0., QObject *parent = 0)
        : Worker(parent)
        , x_(x)
    {}

    void doWork();
    void saveXToFile();

signals:
    void sigUpdateY(double x, double y);
    void sigSaveXToFile(double x);

private:
    double x_;
};

#endif // MATHWORKER_H
