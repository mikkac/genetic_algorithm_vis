#include "environment.hpp"

#include <spdlog/spdlog.h>

#include <numeric>

#include "utils.hpp"

namespace {
void printEnvironment(const gen::Environment::Population population,
                      const auto& estimates, const auto& probs,
                      const auto& ranges) {
    spdlog::info("Environment:");
    for (std::size_t i{0}; i < population.size(); ++i) {
        spdlog::info(
            "\tValue: {:8d}\t\testimate: {:8f}\t\tprob: {:8f}\t\trange: {:8f}",
            population[i].getValue(), estimates[i], probs[i], ranges[i]);
    }
}
}  // namespace

namespace gen {
Environment::Environment(std::size_t individuals_n,
                         EstimateFunction&& estimate_func)
    : m_population{individuals_n}, m_estimate_func{std::move(estimate_func)} {}

void Environment::run(std::size_t steps) {
    spdlog::info("Running simulation with {} steps", steps);
    for (std::size_t step{0}; step < steps; ++step) {
        spdlog::info("Step {}", step + 1);

        // Estimates
        std::vector<float> estimates(m_population.size());
        for (std::size_t i{0}; i < m_population.size(); ++i) {
            estimates[i] = m_estimate_func(m_population[i]);
        }

        const auto total_estimation{
            std::accumulate(std::cbegin(estimates), std::cend(estimates), 0)};

        // Reproduction probabilities
        std::vector<float> reproduction_probs(m_population.size());
        spdlog::debug("Total estimation: {}", total_estimation);
        for (std::size_t i{0}; i < m_population.size(); ++i) {
            reproduction_probs[i] = estimates[i] / total_estimation;
        }

        const auto total_prob{std::accumulate(std::cbegin(reproduction_probs),
                                              std::cend(reproduction_probs),
                                              0.0)};

        // Cake
        std::vector<float> probabilities_ranges(m_population.size());
        std::transform(
            std::cbegin(reproduction_probs), std::cend(reproduction_probs),
            std::begin(probabilities_ranges),
            [sum = 0.0](const auto& next) mutable { return sum += next; });

        // Population candidates
        const auto find_candidate_index =
            [&probabilities_ranges, this](const auto& probability) -> int {
            for (std::size_t i{0}; i < probabilities_ranges.size(); ++i) {
                if (probability <= probabilities_ranges[i]) return i;
            }
            return -1;
        };

        printEnvironment(m_population, estimates, reproduction_probs,
                         probabilities_ranges);

        std::vector<Individual> candidates(m_population.size());
        for (auto& candidate : candidates) {
            candidate = m_population[find_candidate_index(random_d())];
        }
        printPopulation(candidates);
    }
}

void Environment::printPopulation() const { printPopulation(m_population); }

void Environment::printPopulation(const Population& population) const {
    spdlog::info("Candidates:");
    for (const auto& individual : population)
        spdlog::info("\tvalue: {}\testimate: {}", individual.getValue(),
                     m_estimate_func(individual));
}
}  // namespace gen