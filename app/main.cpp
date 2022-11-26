#include <spdlog/spdlog.h>

#include <QApplication>
#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QThread>

#include "algorithm_controller.hpp"
#include "algorithm_data_model.hpp"

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    auto *algo_controller{new gen::AlgorithmController(&app)};
    auto *algo_data_model{new gen::AlgorithmDataModel(&app)};
    QObject::connect(algo_controller, &gen::AlgorithmController::signalFinished,
                     algo_data_model, &gen::AlgorithmDataModel::slotFinished);

    engine.rootContext()->setContextProperty("AlgorithmController",
                                             algo_controller);
    engine.rootContext()->setContextProperty("AlgorithmDataModel",
                                             algo_data_model);

    const QUrl url(u"qrc:/genetic_algorithm/main.qml"_qs);
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl) QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
