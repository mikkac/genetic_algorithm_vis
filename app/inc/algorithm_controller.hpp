#pragma once

#include <QObject>
#include <QThread>

#include "algorithm_result.hpp"
#include "environment.hpp"
namespace gen {
class AlgorithmController : public QObject {
    Q_OBJECT

   public:
    AlgorithmController(QObject* parent = nullptr);

   signals:
    void signalFinished(gen::AlgorithmResult results);
    void signalEstimationFunctionReady(
        std::vector<std::pair<double, double>> data);

   public slots:
    void slotRunAlgorithm(std::size_t population_size, std::size_t steps,
                          int initial_min, int initial_max,
                          double mutation_probability,
                          std::size_t mutated_bits_n, std::size_t crossing_pos);

   private:
    std::vector<std::pair<double, double>> generateEstimationFuncData(
        const AlgorithmConfig::EstimateFunction& estimation_func);

   private:
    QThread* m_worker_thread;
};
}  // namespace gen
