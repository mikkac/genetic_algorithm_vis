#include "algorithm_data_model.hpp"

#include <spdlog/spdlog.h>

AlgorithmDataModel::AlgorithmDataModel(QObject* parent)
    : QAbstractTableModel(parent) {}

void AlgorithmDataModel::slotFinished(const std::vector<double>& results) {
    // Reset ranges
    m_x_min = -10;
    m_x_max = results.size() * 1.05;
    m_y_min = qInf();
    m_y_max = -qInf();

    // Remove old data
    beginResetModel();
    m_data.clear();
    endResetModel();

    // Insert new data
    beginInsertRows(QModelIndex(), 0, results.size() - 1);
    for (int i = 0; i < results.size(); ++i) {
        m_data.append(qMakePair(qreal(i), results[i]));
        m_y_min = std::min(m_y_min, results[i]);
        m_y_max = std::max(m_y_max, results[i]);
    }
    m_y_min *= 0.9;
    m_y_max *= 1.1;
    endInsertRows();

    emit signalDataChanged();
}

int AlgorithmDataModel::rowCount(const QModelIndex& index) const {
    Q_UNUSED(index);
    return m_data.size();
}

int AlgorithmDataModel::columnCount(const QModelIndex& index) const {
    Q_UNUSED(index);
    return 2;
}

QVariant AlgorithmDataModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || role != Qt::DisplayRole) return QVariant();

    if (index.column() == 0) {
        spdlog::info("Column0: {}", m_data.at(index.row()).first);
        return m_data.at(index.row()).first;
    }
    if (index.column() == 1) {
        spdlog::info("Column1: {}", m_data.at(index.row()).second);
        return m_data.at(index.row()).second;
    }
    return QVariant();
}

double AlgorithmDataModel::getXMin() const { return m_x_min; }
double AlgorithmDataModel::getXMax() const { return m_x_max; }
double AlgorithmDataModel::getYMin() const { return m_y_min; }
double AlgorithmDataModel::getYMax() const { return m_y_max; }
