#include <spdlog/spdlog.h>

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "algorithm_data_model.hpp"
// #include "configparser.hpp"
// #include "environment.hpp"

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
    engine.rootContext()->setContextProperty("AlgorithmDataModel",
                                             new AlgorithmDataModel());
    const QUrl url(u"qrc:/genetic_algorithm/main.qml"_qs);
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl) QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();

    // gen::Environment env{10, [](const gen::Individual& individual) -> double
    // {
    //                          const auto x{individual.getValue()};
    //                          return x * x;
    //                      }};

    // env.run(1);

    return 0;
}
