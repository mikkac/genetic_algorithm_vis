#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QThread>
#include <QObject>

class WorkerThread : public QThread
{
   public:
    explicit WorkerThread(QObject *parent = nullptr);
};

#endif // WORKERTHREAD_H
