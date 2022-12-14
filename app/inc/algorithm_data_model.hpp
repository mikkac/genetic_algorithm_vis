#pragma once

#include <QAbstractTableModel>
#include <QPair>

#include "algorithm_result.hpp"

namespace gen {
class AlgorithmDataModel : public QAbstractTableModel {
    Q_OBJECT

    Q_PROPERTY(double xMin READ getXMin NOTIFY signalDataChanged)
    Q_PROPERTY(double xMax READ getXMax NOTIFY signalDataChanged)
    Q_PROPERTY(double yMin READ getYMin NOTIFY signalDataChanged)
    Q_PROPERTY(double yMax READ getYMax NOTIFY signalDataChanged)

   public:
    AlgorithmDataModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index,
                  int role = Qt::DisplayRole) const override;

    double getXMin() const;
    double getXMax() const;
    double getYMin() const;
    double getYMax() const;

   signals:
    void signalDataChanged();

   public slots:
    void slotFinished(gen::AlgorithmResult result);
    void slotSetEstimationFuncData(std::vector<std::pair<double, double>> data);

   private:
    AlgorithmResult m_data;
    std::vector<std::pair<double, double>> m_estimation_func_data;
    double m_x_min{0.0};
    double m_x_max{1.0};
    double m_y_min{0.0};
    double m_y_max{1.0};
};
}  // namespace gen
