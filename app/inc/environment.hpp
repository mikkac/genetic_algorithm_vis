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
    Population m_population;
    std::size_t m_steps;
    EstimateFunction m_estimate_func;
    std::vector<double> m_avg_estimations;
    double m_mutation_prob{0.01};
};
}  // namespace gen
