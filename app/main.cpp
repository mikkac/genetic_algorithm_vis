#include <spdlog/spdlog.h>

#include <QApplication>
#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QThread>

#include "algorithm_controller.hpp"
#include "algorithm_data_model.hpp"
// #include "configparser.hpp"

int main(int argc, char **argv) {
    // gen::Configuration config;
    // int parsing_result{};
    // if (argc > 1) {
    //     spdlog::info("Parameters will be loaded from CMD");
    //     if (const auto parsing_result{config.parseCmd(argc, argv)};
    //         parsing_result)
    //         return parsing_result;
    // }

    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    auto *algo_controller{new AlgorithmController(&app)};
    auto *algo_data_model{new AlgorithmDataModel(&app)};
    QObject::connect(algo_controller, &AlgorithmController::signalFinished,
                     algo_data_model, &AlgorithmDataModel::slotFinished);

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

    //    gen::Environment env{
    //        10, [](const gen::Individual& individual) -> double {
    //            const auto x{(int32_t)individual.getValue().to_ulong()};
    //            return 1 * x * x;
    //        }};

    //    env.run(30);

    //    return 0;
}
