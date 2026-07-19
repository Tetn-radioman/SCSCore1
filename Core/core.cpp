#include "core.h"
#include "appbus.h"
#include "configmanager.h"
#include "../Modules/ExampleModule/examplemodule.h"
#include <QCoreApplication>
#include <QDebug>

Core::Core(QObject *parent) : QObject(parent) {
    m_manager = CoreManager::instance();

    // Подписка ядра на события
    connect(AppBus::instance(), &AppBus::eventReceived,
            this, &Core::onCoreEvent);
}

Core::~Core() {
    shutdown();
}

void Core::start() {
    qDebug() << "[CORE] Инициализация ядра...";

    // 1. Загружаем конфиг
    ConfigManager::instance()->loadConfig("config.json");

    // 2. Регистрируем модули
    registerAllModules();

    // 3. Запускаем все модули
    m_manager->startAllModules();

    qDebug() << "[CORE] Ядро запущено!";
}

void Core::shutdown() {
    qDebug() << "[CORE] Остановка ядра...";
    m_manager->shutdownAllModules();
}

void Core::registerAllModules() {
    // ЗДЕСЬ ДОБАВЛЯЕМ ВСЕ МОДУЛИ
    m_manager->registerModule(new ExampleModule());

    // Пример добавления нового модуля:
    // m_manager->registerModule(new NetworkModule());
    // m_manager->registerModule(new LoggerModule());
}

void Core::onCoreEvent(EventType type, const QJsonObject &data) {
    // Ядро обрабатывает только системные события
    if (type == EventType::SystemShutdown) {
        shutdown();
        QCoreApplication::quit();
    }
}
