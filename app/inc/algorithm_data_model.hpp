#pragma once

#include <QList>
#include <QObject>
#include <QPointF>
#include <QTimer>

class AlgorithmDataModel : public QObject {
    Q_OBJECT
    Q_PROPERTY(QVector<QPointF> data READ getData NOTIFY signalDataChanged)

   public:
    AlgorithmDataModel(QObject* parent = nullptr);
    QVector<QPointF> getData() const { return m_data; }

   signals:
    void signalDataChanged();

   public slots:
    void slotFinished(const std::vector<double>& results);

   private:
    QVector<QPointF> m_data{};
};
