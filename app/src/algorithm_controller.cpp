#include "algorithm_controller.hpp"

#include "environment.hpp"

AlgorithmController::AlgorithmController(QObject* parent) : QObject(parent) {}

void AlgorithmController::slotRunAlgorithm() {
    std::size_t population_size{100};
    std::size_t iterations{300};

    auto estimation_func{[](const gen::Individual& individual) -> double {
        const auto x{(int32_t)individual.getValue().to_ulong()};
        return 1 * x * x;
    }};
    auto* env{
        new gen::Environment{population_size, std::move(estimation_func)}};

    m_worker_thread = new QThread;
    connect(env, &gen::Environment::signalFinished, this,
            &AlgorithmController::signalFinished);
    env->moveToThread(m_worker_thread);
    env->run(iterations);
}
