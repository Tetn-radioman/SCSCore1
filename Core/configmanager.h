#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QDebug>

class ConfigManager : public QObject {
    Q_OBJECT
public:
    static ConfigManager* instance();

    // Загрузить конфиг из файла
    bool loadConfig(const QString &path);

    // Получить конфиг для конкретного модуля
    QJsonObject getModuleConfig(const QString &moduleName);

    // Получить глобальную настройку
    QJsonValue getValue(const QString &key);

private:
    explicit ConfigManager(QObject *parent = nullptr);
    static ConfigManager *m_instance;
    QJsonObject m_config;
};

#endif // CONFIGMANAGER_H
