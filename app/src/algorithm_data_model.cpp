#include "algorithm_data_model.hpp"

AlgorithmDataModel::AlgorithmDataModel(QObject* parent) : QObject(parent) {}

void AlgorithmDataModel::slotFinished(const std::vector<double>& results) {
    m_data.clear();
    for (int i = 0; i < results.size(); ++i) {
        m_data.push_back(QPointF{qreal(i), results[i]});
    }

    emit signalDataChanged();
}
