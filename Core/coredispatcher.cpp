#include "coredispatcher.h"
#include "appbus.h"
#include <QDebug>

CoreDispatcher::CoreDispatcher(QObject *parent)
    : QObject(parent) {
    m_pool.setMaxThreadCount(8);
}

void CoreDispatcher::onTaskFinished(const QJsonObject &result) {
    AppBus::instance()->send(EventType::ResultReady, result);
}

// Реализация для void функций
void CoreDispatcher::dispatch(std::function<void()> task) {
    QtConcurrent::run(&m_pool, [this, task]() {
        task();
        QJsonObject empty;
        empty["status"] = "done";
        onTaskFinished(empty);
    });
}
