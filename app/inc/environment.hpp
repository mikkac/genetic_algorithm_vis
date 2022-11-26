#pragma once

#include <spdlog/spdlog.h>

#include <QObject>
#include <cstdint>
#include <functional>

#include "algorithm_config.hpp"
#include "algorithm_result.hpp"
#include "individual.hpp"

namespace gen {
class Environment : public QObject {
    Q_OBJECT
   public:
    using Population = std::vector<Individual>;

    explicit Environment(AlgorithmConfig&& config);

    void printPopulation() const;
    void printPopulation(const Population& population,
                         const std::string& desc) const;

   signals:
    void signalStart();
    void signalFinished(AlgorithmResult result);

   private slots:
    void slotStarted();

   private:
    Population m_population{};
    AlgorithmConfig m_config{};
};
}  // namespace gen
