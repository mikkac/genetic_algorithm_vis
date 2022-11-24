#pragma once

#include <QObject>
#include <QThread>

class AlgorithmController : public QObject {
    Q_OBJECT

   public:
    AlgorithmController(QObject* parent = nullptr);

   signals:
    void signalFinished(const std::vector<double> results);

   public slots:
    void slotRunAlgorithm();

   private:
    QThread* m_worker_thread;
};
