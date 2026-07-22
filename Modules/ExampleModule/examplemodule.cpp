#include "examplemodule.h"//            свой заговолок
#include "../../Core/configmanager.h"// менеджер конфигов
#include <QDebug>//                     отладка
#include <QTimer>

ExampleModule::ExampleModule(QObject *parent)// конструктор
    : IModule(parent) {// вызываем конструктор родителя
    // Подписываемся на события
    connect(AppBus::instance(), &AppBus::eventReceived,
            this, &ExampleModule::onEvent);// connect(отправитель, &Класс::сигнал, получатель, &Класс::слот);
}

ExampleModule::~ExampleModule() {// деструктор
    // Отписываемся
    disconnect(AppBus::instance(), nullptr, this, nullptr);// отключает все соединения от этого объекта
}

bool ExampleModule::init() {// сердце модуля
    qDebug() << "[ExampleModule] Инициализация...";

    // Загружаем конфиг для модуля
    auto config = ConfigManager::instance()->getModuleConfig("example");
    if (!config.isEmpty()) {
        qDebug() << "[ExampleModule] Настройки:" << config;
    }

    // Отправляем тестовое событие через 1 сек
    QTimer::singleShot(1000, []() {
        QJsonObject data;
        data["message"] = "Hello from ExampleModule!";
        AppBus::instance()->send(EventType::TestEvent, data);
    });

    return true;
}

void ExampleModule::shutdown() {
    qDebug() << "[ExampleModule] Остановка...";
}

void ExampleModule::onEvent(EventType type, const QJsonObject &data) {
    switch (type) {
    case EventType::TestEvent:
        handleTestEvent(data);
        break;
    default:
        break;
    }
}

void ExampleModule::handleTestEvent(const QJsonObject &data) {
    qDebug() << "[ExampleModule] Получено тестовое событие:";
    qDebug() << "  Сообщение:" << data["message"].toString();

    // Отправляем результат
    QJsonObject result;
    result["module"] = name();
    result["status"] = "success";
    result["data"] = data;

    AppBus::instance()->send(EventType::ResultReady, result);
}
