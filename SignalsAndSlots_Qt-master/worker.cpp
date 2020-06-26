#include "worker.h"


void Worker::slotPause()
{
    auto const dispatcher = QThread::currentThread()->eventDispatcher();
    if (!dispatcher) {
        //throw std::runtime_error("thread with no dispatcher");
        return;
    }

    if (state != RUNNING)
        return;

    state = PAUSED;

    do {
        dispatcher->processEvents(QEventLoop::WaitForMoreEvents);
    } while (state == PAUSED);
}

void Worker::slotResume()
{
    if (state == PAUSED) {
        state = RUNNING;
    }
}

void Worker::slotCancel() {
    if (state != STOPPED) {
        state = STOPPED;
    }
}

bool Worker::isCancelled() const  {
    auto const dispatcher = QThread::currentThread()->eventDispatcher();
    if (!dispatcher) {
        //throw std::runtime_error("thread with no dispatcher");
        return false;
    }
    dispatcher->processEvents(QEventLoop::AllEvents);
    return state == STOPPED;
}
