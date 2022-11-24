#include "algorithm_data_model.hpp"

#include "environment.hpp"

AlgorithmDataModel::AlgorithmDataModel(QObject* parent) : QObject(parent) {}

void AlgorithmDataModel::slotGenerateData() {
    gen::Environment env{
        100, [](const gen::Individual& individual) -> double {
            const auto x{(int32_t)individual.getValue().to_ulong()};
            return 1 * x * x;
        }};

    env.run(300);
    const auto results{env.getResults()};
    m_data.clear();
    for (int i = 0; i < results.size(); ++i) {
        m_data.push_back(QPointF{qreal(i), results[i]});
    }

    emit dataChanged();
}
