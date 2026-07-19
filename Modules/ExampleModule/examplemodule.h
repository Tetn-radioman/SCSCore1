#ifndef EXAMPLEMODULE_H
#define EXAMPLEMODULE_H

#include "imodule.h"
#include "appbus.h"

class ExampleModule : public IModule {
    Q_OBJECT
public:
    explicit ExampleModule(QObject *parent = nullptr);
    ~ExampleModule();

    bool init() override;
    void shutdown() override;
    QString name() const override { return "ExampleModule"; }

    void onEvent(EventType type, const QJsonObject &data) override;

private:
    void handleTestEvent(const QJsonObject &data);
};

#endif
