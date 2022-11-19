#include "algorithm_data_model.hpp"

#include <spdlog/spdlog.h>

void AlgorithmDataModel::slotGenerateData() {
    for (int i = 0; i < 1000; ++i) {
        m_data.push_back(QPointF{qreal(i), i * i * 0.1});
    }

    emit dataChanged();
}

AlgorithmDataModel::AlgorithmDataModel(QObject *parent) : QObject(parent) {
    //    m_timer = new QTimer(this);
    //    m_timer->setInterval(1000);
    //    m_timer->setSingleShot(true);
    //    connect(m_timer, &QTimer::timeout, this,
    //    &AlgorithmDataModel::slotTimeout); m_timer->start();
}
