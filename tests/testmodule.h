#ifndef TESTMODULE_H
#define TESTMODULE_H

#include "coremanager.h"
#include "appbus.h"
#include <QJsonObject>
#include <QThread>

class TestModule : public IModule {
    Q_OBJECT
public:
    explicit TestModule(QObject *parent = nullptr);

    // IModule interface
    bool init() override;
    void shutdown() override;
    QString name() const override { return "TestModule"; }

private slots:
    void onEventReceived(EventType type, QJsonObject data);

private:
    void handleStartCheck(const QJsonObject &data);
};

#endif // TESTMODULE_H
