#ifndef COREDISPATCHER_H
#define COREDISPATCHER_H

#include <QObject>
#include <QThreadPool>
#include <QFuture>
#include <QtConcurrent/QtConcurrentRun>
#include <QJsonObject>
#include <functional>

class CoreDispatcher : public QObject {
    Q_OBJECT
public:
    explicit CoreDispatcher(QObject *parent = nullptr);

    // Главный метод: запускает любую функцию в потоке
    template<typename Function>
    void dispatch(Function task) {
        QtConcurrent::run(&m_pool, [this, task]() {
            auto result = task();
            onTaskFinished(result);
        });
    }

    // Специализация для void функций (без результата)
    void dispatch(std::function<void()> task);

private:
    void onTaskFinished(const QJsonObject &result);

private:
    QThreadPool m_pool;
};

#endif // COREDISPATCHER_H
