#ifndef IMODULE_H
#define IMODULE_H

#include <QObject>// сигналы слоты и т д
#include <QJsonObject>// КОНТЕЙНЕР ДЛЯ КЛАССОВ

#include "appbus.h"

class IModule : public QObject {
    Q_OBJECT
public:
    explicit IModule(QObject *parent = nullptr) : QObject(parent) {}
    virtual ~IModule() = default;

    virtual bool init() = 0; // 1 - готов к работе 2 - что-то не так модуль не загружается
    virtual void shutdown() = 0;
    virtual QString name() const = 0;

    // Обработка событий
    virtual void onEvent(EventType type, const QJsonObject &data) = 0;
};

#endif
