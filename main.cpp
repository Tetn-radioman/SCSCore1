#include <QCoreApplication>
#include "Core/core.h"

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    Core core;
    core.start();

    return app.exec();
}
