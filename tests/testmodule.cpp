#include "testmodule.h"
#include "coredispatcher.h"
#include "configmanager.h"
#include <QTimer>
#include <QDateTime>

TestModule::TestModule(QObject *parent)
    : IModule(parent) {
    // Подписываемся на события
    connect(AppBus::instance(), &AppBus::eventReceived,
            this, &TestModule::onEventReceived);
}

bool TestModule::init() {
    qDebug() << "[TestModule] Инициализация...";
    auto config = ConfigManager::instance()->getModuleConfig("testmodule");
    if (!config.isEmpty()) {
        qDebug() << "[TestModule] Настройки:" << config;
    }
    return true;
}

void TestModule::shutdown() {
    qDebug() << "[TestModule] Остановка...";
}

void TestModule::onEventReceived(EventType type, QJsonObject data) {
    switch (type) {
    case EventType::StartCheck:
        handleStartCheck(data);
        break;

    case EventType::ConfigLoaded:
        qDebug() << "[TestModule] Конфиг обновлен!";
        break;

    default:
        break;
    }
}

void TestModule::handleStartCheck(const QJsonObject &data) {
    qDebug() << "[TestModule] Получена команда StartCheck";
    qDebug() << "[TestModule] Данные:" << data;

    CoreDispatcher dispatcher;
    dispatcher.dispatch([this]() -> QJsonObject {
        qDebug() << "[TestModule] Выполняю проверку в потоке"
                 << QThread::currentThreadId();

        QThread::sleep(3);

        QJsonObject result;
        result["module"] = "TestModule";
        result["status"] = "success";
        result["message"] = "Проверка выполнена успешно";
        result["thread_id"] = (qint64)QThread::currentThreadId();
        result["timestamp"] = QDateTime::currentDateTime().toString();

        // ОТПРАВЛЯЕМ РЕЗУЛЬТАТ!
        AppBus::instance()->send(EventType::ResultReady, result);

        return result;
    });
}
