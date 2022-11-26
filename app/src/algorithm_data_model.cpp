#include "algorithm_data_model.hpp"

namespace gen {
AlgorithmDataModel::AlgorithmDataModel(QObject* parent)
    : QAbstractTableModel(parent) {}

void AlgorithmDataModel::slotFinished(AlgorithmResult result) {
    // Reset ranges
    m_x_min = -3;
    m_x_max = result.steps.size() * 1.05;
    m_y_min = qInf();
    m_y_max = -qInf();

    // Remove old data
    beginResetModel();
    m_data = {};
    endResetModel();

    // Insert new data
    beginInsertRows(QModelIndex(), 0, result.steps.size() - 1);
    m_data = std::move(result);
    const auto min{
        *std::min_element(std::cbegin(m_data.min), std::cend(m_data.min))};
    const auto max{
        *std::max_element(std::cbegin(m_data.max), std::cend(m_data.max))};
    m_y_min = min * 0.9;
    m_y_max = max * 1.1;
    endInsertRows();

    emit signalDataChanged();
}

void AlgorithmDataModel::slotSetEstimationFuncData(
    std::vector<std::pair<double, double> > data) {
    m_estimation_func_data = std::move(data);
}

int AlgorithmDataModel::rowCount(const QModelIndex& index) const {
    Q_UNUSED(index);
    return m_data.steps.size();
}

int AlgorithmDataModel::columnCount(const QModelIndex& index) const {
    Q_UNUSED(index);
    return 4;
}

QVariant AlgorithmDataModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || role != Qt::DisplayRole) return QVariant();

    if (index.column() == 0) return m_data.steps.at(index.row());

    if (index.column() == 1) return m_data.avg.at(index.row());

    if (index.column() == 2) return m_data.min.at(index.row());

    if (index.column() == 3) return m_data.max.at(index.row());
    return QVariant();
}

double AlgorithmDataModel::getXMin() const { return m_x_min; }
double AlgorithmDataModel::getXMax() const { return m_x_max; }
double AlgorithmDataModel::getYMin() const { return m_y_min; }
double AlgorithmDataModel::getYMax() const { return m_y_max; }
}  // namespace gen
