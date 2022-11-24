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

    explicit Environment(std::size_t individuals_n,
                         EstimateFunction&& estimate_func);

    void run(std::size_t steps);

    void printPopulation() const;
    void printPopulation(const Population& population,
                         const std::string& desc) const;

    std::vector<double> getResults() const;

   signals:
    void signalFinished(const std::vector<double>& results);

   private:
    Population m_population;
    EstimateFunction m_estimate_func;
    std::vector<double> m_avg_estimations;
    double m_mutation_prob{0.01};
};
}  // namespace gen
