#include "configmanager.h"

ConfigManager* ConfigManager::m_instance = nullptr;

ConfigManager::ConfigManager(QObject *parent)
    : QObject(parent) {}

ConfigManager* ConfigManager::instance() {
    if (!m_instance) {
        m_instance = new ConfigManager();
    }
    return m_instance;
}

bool ConfigManager::loadConfig(const QString &path) {
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "[Config] Ошибка: не могу открыть файл" << path;
        return false;
    }

    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);

    if (doc.isNull()) {
        qDebug() << "[Config] Ошибка: неверный JSON";
        return false;
    }

    m_config = doc.object();
    qDebug() << "[Config] Загружен файл" << path;
    return true;
}

QJsonObject ConfigManager::getModuleConfig(const QString &moduleName) {
    return m_config[moduleName].toObject();
}

QJsonValue ConfigManager::getValue(const QString &key) {
    return m_config[key];
}
