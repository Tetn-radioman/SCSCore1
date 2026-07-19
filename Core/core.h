#ifndef CORE_H
#define CORE_H

#include <QObject>
#include "coremanager.h"

class Core : public QObject {
    Q_OBJECT
public:
    explicit Core(QObject *parent = nullptr);
    ~Core();

    void start();
    void shutdown();

private:
    void registerAllModules();  // Здесь регистрируем ВСЕ модули
    void onCoreEvent(EventType type, const QJsonObject &data);

    CoreManager* m_manager;
};

#endif
