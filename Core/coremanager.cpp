#include "coremanager.h"
#include "configmanager.h"
#include "appbus.h"

CoreManager* CoreManager::m_instance = nullptr;

CoreManager::CoreManager(QObject *parent)
    : QObject(parent) {}

CoreManager* CoreManager::instance() {
    if (!m_instance) {
        m_instance = new CoreManager();
    }
    return m_instance;
}

void CoreManager::registerModule(IModule *module) {
    if (!module) return;

    QString name = module->name();
    if (m_modules.contains(name)) {
        qDebug() << "[CoreManager] Модуль уже зарегистрирован:" << name;
        return;
    }

    m_modules[name] = module;
    qDebug() << "[CoreManager] Зарегистрирован модуль:" << name;
}

void CoreManager::startAllModules() {
    qDebug() << "[CoreManager] Запуск всех модулей...";

    for (auto it = m_modules.begin(); it != m_modules.end(); ++it) {
        QString name = it.key();
        IModule *module = it.value();

        qDebug() << "[CoreManager] Запуск модуля:" << name;

        if (!module->init()) {
            qDebug() << "[CoreManager] Ошибка запуска модуля:" << name;
        } else {
            qDebug() << "[CoreManager] Модуль запущен:" << name;
        }
    }
}

void CoreManager::shutdownAllModules() {
    qDebug() << "[CoreManager] Остановка всех модулей...";

    for (auto it = m_modules.begin(); it != m_modules.end(); ++it) {
        it.value()->shutdown();
        qDebug() << "[CoreManager] Остановлен модуль:" << it.key();
    }
}

bool CoreManager::isModuleLoaded(const QString &name) const {
    return m_modules.contains(name);
}
