#include "appbus.h"
#include <QMetaObject>
#include <QCoreApplication>

AppBus* AppBus::m_instance = nullptr;

AppBus::AppBus(QObject *parent)
    : QObject(parent) {
    // Убеждаемся, что объект живёт в главном потоке
    moveToThread(QCoreApplication::instance()->thread());
}

AppBus* AppBus::instance() {
    if (!m_instance) {
        m_instance = new AppBus();
    }
    return m_instance;
}

void AppBus::send(EventType type, const QJsonObject &data) {
    QMutexLocker locker(&m_mutex);

    // Используем Qt::QueuedConnection, чтобы сигнал прилетел в главный поток
    // даже если вызов сделан из другого потока
    QMetaObject::invokeMethod(this, [this, type, data]() {
        emit eventReceived(type, data);
    }, Qt::QueuedConnection);
}
