#include "environment.hpp"

#include <spdlog/spdlog.h>

#include <numeric>

#include "utils.hpp"

namespace {
void printEnvironment(const gen::Environment::Population population,
                      const auto& estimates, const auto& probs,
                      const auto& ranges) {
    //    spdlog::info("Environment:");
    //    for (std::size_t i{0}; i < population.size(); ++i) {
    //        spdlog::info(
    //            "\tValue: {:8d}\t\testimate: {:8f}\t\tprob: {:8f}\t\trange:
    //            {:8f}", (int32_t)population[i].getValue().to_ulong(),
    //            estimates[i], probs[i], ranges[i]);
    //    }
}

int toggleBit(int number, int bit_number) {
    return number ^= 1UL << bit_number;
}

gen::Individual cross(const gen::Individual& first,
                      const gen::Individual& second, std::size_t cross_pos) {
    const auto first_val{first.getValue()};
    const auto second_val{second.getValue()};
    if (first_val.size() != second_val.size()) return gen::Individual{0};

    gen::Individual::UnderlyingType crossed;
    for (std::size_t i{}; i < first_val.size(); ++i) {
        if (i < cross_pos) {
            crossed[i] = first_val[i];
        } else {
            crossed[i] = second_val[i];
        }
    }
    return gen::Individual{crossed};
}

gen::Individual mutate(const gen::Individual& individual, std::size_t bit) {
    if (bit >= individual.getValue().size()) return gen::Individual{0};
    auto mutated{individual.getValue()};
    mutated.flip(bit);
    return gen::Individual{mutated};
}

}  // namespace

namespace gen {
Environment::Environment(AlgorithmConfig&& config)
    : m_population{config.population_size}, m_config{config} {
    connect(this, &Environment::signalStart, this, &Environment::slotStarted);
}

void Environment::printPopulation() const {
    printPopulation(m_population, "Population");
}

void Environment::printPopulation(const Population& population,
                                  const std::string& desc) const {
    //    spdlog::info(desc);
    //    for (const auto& individual : population)
    //        spdlog::info("\tvalue: {}\testimate: {}",
    //                     (int32_t)individual.getValue().to_ulong(),
    //                     m_estimate_func(individual));
}

void Environment::slotStarted() {
    spdlog::info("Running simulation with {} steps", m_config.steps);
    AlgorithmResult result{};
    for (std::size_t step{0}; step < m_config.steps; ++step) {
        spdlog::info("Step {}", step + 1);
        result.steps.push_back(step + 1);
        // Estimates
        std::vector<float> estimates(m_population.size());
        for (std::size_t i{0}; i < m_population.size(); ++i) {
            estimates[i] = m_config.estimate_func(m_population[i]);
        }

        const auto total_estimation{
            std::accumulate(std::cbegin(estimates), std::cend(estimates), 0)};

        result.avg.push_back(total_estimation / m_population.size());
        const auto [min, max]{
            std::minmax_element(std::cbegin(estimates), std::cend(estimates))};
        result.min.push_back(*min);
        result.max.push_back(*max);

        // Reproduction probabilities
        std::vector<float> reproduction_probs(m_population.size());
        spdlog::debug("Total estimation: {}", total_estimation);
        for (std::size_t i{0}; i < m_population.size(); ++i) {
            reproduction_probs[i] = estimates[i] / total_estimation;
        }

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
        printPopulation(candidates, "Candidates");

        // Cross
        std::vector<Individual> crossed(m_population.size());
        for (int i{0}; i < candidates.size() - 1; ++i) {
            crossed[i] =
                cross(candidates[i], candidates[i + 1], m_config.crossing_pos);
        }
        printPopulation(crossed, "Crossed");

        // Mutate
        std::vector<Individual> mutated;
        mutated.reserve(m_population.size());
        for (const auto& cross : crossed) {
            if (random_d() < m_config.mutation_probability) {
                mutated.push_back(mutate(
                    cross,
                    random_i(
                        0, m_config.mutated_bits_n)));  // Individual::Size - 1
            } else {
                mutated.push_back(cross);
            }
        }
        printPopulation(mutated, "Mutated");

        // Succession
        m_population = std::move(mutated);
    }

    emit signalFinished(result);
}

}  // namespace gen
