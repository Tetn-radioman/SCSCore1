#ifndef COREMANAGER_H
#define COREMANAGER_H

#include <QObject>
#include <QMap>
#include <QString>
#include <QDebug>

#include "imodule.h"

class CoreManager : public QObject {
    Q_OBJECT
public:
    static CoreManager* instance();

    // Зарегистрировать модуль
    void registerModule(IModule *module);

    // Запустить все модули
    void startAllModules();

    // Остановить все модули
    void shutdownAllModules();

    // Проверить, загружен ли модуль
    bool isModuleLoaded(const QString &name) const;

private:
    explicit CoreManager(QObject *parent = nullptr);
    static CoreManager *m_instance;
    QMap<QString, IModule*> m_modules;
};

#endif // COREMANAGER_H
