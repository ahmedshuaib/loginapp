#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include <QThread>

class MainController : public QObject
{
    Q_OBJECT
    QThread worker_thread;
public:
    explicit MainController(QObject *parent = nullptr);

signals:

public slots:
};

#endif // MAINCONTROLLER_H
