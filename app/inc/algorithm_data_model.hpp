#pragma once

#include <QList>
#include <QObject>
#include <QPointF>
#include <QTimer>

class AlgorithmDataModel : public QObject {
    Q_OBJECT
    Q_PROPERTY(QVector<QPointF> data READ getData NOTIFY dataChanged)

   public:
    AlgorithmDataModel(QObject *parent = Q_NULLPTR);
    QVector<QPointF> getData() const { return m_data; }

   signals:
    void dataChanged();

   public slots:
    void slotGenerateData();

   private:
    QVector<QPointF> m_data{};
};
