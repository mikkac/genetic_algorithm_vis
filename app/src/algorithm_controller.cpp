#include "algorithm_controller.hpp"

#include "environment.hpp"

AlgorithmController::AlgorithmController(QObject* parent) : QObject(parent) {}

void AlgorithmController::slotRunAlgorithm(std::size_t individuals_n,
                                           std::size_t steps,
                                           double mutation_probability,
                                           std::size_t mutated_bits_n,
                                           std::size_t crossing_pos) {
    std::size_t population_size{100};
    std::size_t iterations{1000};
    auto estimation_func{[](const gen::Individual& individual) -> double {
        const auto x{(int32_t)individual.getValue().to_ulong()};
        return 1 * x * x;
    }};
    auto* env{new gen::Environment{individuals_n, steps, mutation_probability,
                                   mutated_bits_n, crossing_pos,
                                   std::move(estimation_func)}};

    m_worker_thread = new QThread;
    connect(env, &gen::Environment::signalFinished, this,
            &AlgorithmController::signalFinished);
    env->moveToThread(m_worker_thread);
    m_worker_thread->start();
    emit env->signalStart();
}
