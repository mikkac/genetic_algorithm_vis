#include "algorithm_controller.hpp"

#include "environment.hpp"

namespace gen {
AlgorithmController::AlgorithmController(QObject* parent) : QObject(parent) {}

void AlgorithmController::slotRunAlgorithm(std::size_t population_size,
                                           std::size_t steps, int initial_min,
                                           int initial_max,
                                           double mutation_probability,
                                           std::size_t mutated_bits_n,
                                           std::size_t crossing_pos) {
    auto estimation_func{[](const gen::Individual& individual) -> double {
        const auto x{(int32_t)individual.getValue().to_ulong()};
        return 1 * x * x;
    }};

    gen::AlgorithmConfig config{};
    config.population_size = population_size;
    config.steps = steps;
    config.initial_min = initial_min;
    config.initial_max = initial_max;
    config.mutation_probability = mutation_probability;
    config.mutated_bits_n = mutated_bits_n;
    config.crossing_pos = crossing_pos;
    config.estimate_func = std::move(estimation_func);
    auto* env{new gen::Environment{std::move(config)}};

    m_worker_thread = new QThread;
    connect(env, &gen::Environment::signalFinished, this,
            &AlgorithmController::signalFinished);
    env->moveToThread(m_worker_thread);
    m_worker_thread->start();
    emit env->signalStart();
}
}  // namespace gen
