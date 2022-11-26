#pragma once

#include <spdlog/spdlog.h>

#include <QObject>
#include <cstdint>
#include <functional>

#include "individual.hpp"

namespace gen {
class Environment : public QObject {
    Q_OBJECT
   public:
    using EstimateFunction =
        std::function<double(const Individual& individual)>;

    using Population = std::vector<Individual>;

    explicit Environment(std::size_t individuals_n, std::size_t steps,
                         double mutation_probability,
                         std::size_t mutated_bits_n, std::size_t crossing_pos,
                         EstimateFunction&& estimate_func);

    void printPopulation() const;
    void printPopulation(const Population& population,
                         const std::string& desc) const;

    std::vector<double> getResults() const;

   signals:
    void signalStart();
    void signalFinished(const std::vector<double>& results);

   private slots:
    void slotStarted();

   private:
    Population m_population{};
    std::size_t m_steps{};
    double m_mutation_probability{};
    std::size_t m_mutated_bits_n{};
    std::size_t m_crossing_pos{};
    EstimateFunction m_estimate_func;
    std::vector<double> m_avg_estimations;
};
}  // namespace gen
