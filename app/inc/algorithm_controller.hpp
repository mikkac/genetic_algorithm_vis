#pragma once

#include <QObject>
#include <QThread>

#include "algorithm_result.hpp"

namespace gen {
class AlgorithmController : public QObject {
    Q_OBJECT

   public:
    AlgorithmController(QObject* parent = nullptr);

   signals:
    void signalFinished(gen::AlgorithmResult results);

   public slots:
    void slotRunAlgorithm(std::size_t population_size, std::size_t steps,
                          double mutation_probability,
                          std::size_t mutated_bits_n, std::size_t crossing_pos);

   private:
    QThread* m_worker_thread;
};
}  // namespace gen
