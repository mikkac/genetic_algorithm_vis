#include "estimation_func_data_model.hpp"

#include <spdlog/spdlog.h>
namespace gen {
EstimationFuncDataModel::EstimationFuncDataModel(QObject* parent)
    : QAbstractTableModel(parent) {}

void EstimationFuncDataModel::slotSetEstimationFuncData(
    std::vector<std::pair<double, double>> data) {
    // Reset ranges
    m_x_min = -qInf();
    m_x_max = qInf();
    m_y_min = qInf();
    m_y_max = -qInf();

    // Remove old data
    beginResetModel();
    m_data = {};
    endResetModel();

    // Insert new data
    beginInsertRows(QModelIndex(), 0, data.size() - 1);
    m_data = std::move(data);
    const auto [x_min, x_max]{
        std::minmax_element(std::cbegin(m_data), std::cend(m_data),
                            [](const auto& first, const auto& second) {
                                return first.first < second.first;
                            })};
    m_x_min = x_min->first * 0.9;
    m_x_max = x_max->first * 1.1;

    const auto [y_min, y_max]{
        std::minmax_element(std::cbegin(m_data), std::cend(m_data),
                            [](const auto& first, const auto& second) {
                                return first.second < second.second;
                            })};
    m_y_min = y_min->second * 0.9;
    m_y_max = y_max->second * 1.1;
    endInsertRows();

    emit signalDataChanged();
}

int EstimationFuncDataModel::rowCount(const QModelIndex& index) const {
    Q_UNUSED(index);
    return m_data.size();
}

int EstimationFuncDataModel::columnCount(const QModelIndex& index) const {
    Q_UNUSED(index);
    return 2;
}

QVariant EstimationFuncDataModel::data(const QModelIndex& index,
                                       int role) const {
    if (!index.isValid() || role != Qt::DisplayRole) return QVariant();

    if (index.column() == 0) return m_data.at(index.row()).first;

    if (index.column() == 1) return m_data.at(index.row()).second;
    return QVariant();
}

double EstimationFuncDataModel::getXMin() const { return m_x_min; }
double EstimationFuncDataModel::getXMax() const { return m_x_max; }
double EstimationFuncDataModel::getYMin() const { return m_y_min; }
double EstimationFuncDataModel::getYMax() const { return m_y_max; }
}  // namespace gen
