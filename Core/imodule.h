#ifndef IMODULE_H
#define IMODULE_H

#include <QObject>
#include <QJsonObject>

#include "appbus.h"

class IModule : public QObject {
    Q_OBJECT
public:
    explicit IModule(QObject *parent = nullptr) : QObject(parent) {}
    virtual ~IModule() = default;

    virtual bool init() = 0;
    virtual void shutdown() = 0;
    virtual QString name() const = 0;

    // Обработка событий
    virtual void onEvent(EventType type, const QJsonObject &data) = 0;
};

#endif
