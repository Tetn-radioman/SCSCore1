#ifndef APPBUS_H
#define APPBUS_H

#include <QObject>
#include <QHash>        // для словарей хранение подписок
#include <QList>        // списки
#include <QJsonObject>  // данные событий
#include <QMutex>       // потокобезопасность

// Типы событий, которые могут происходить в системе
enum class EventType {
    StartCheck,         // Начать проверку серверов
    ResultReady,        // Результат проверки готов
    CommandToArduino,   // Отправить команду на Arduino
    LogMessage,         // Логирование
    Shutdown,           // Выключение системы
    ConfigLoaded,       // настройки загружены
    TestEvent,          // Тестовое событие
    SystemShutdown      // Системное завершение
};

class AppBus : public QObject {
    Q_OBJECT
public:
    static AppBus* instance();

    // Отправить событие (из любого потока — потокобезопасно)
    void send(EventType type, const QJsonObject &data = QJsonObject());

signals:
    // Этот сигнал будет пойман в главном потоке
    void eventReceived(EventType type, QJsonObject data);

private:
    explicit AppBus(QObject *parent = nullptr);
    static AppBus *m_instance;
    QMutex m_mutex;
};

#endif // APPBUS_H
