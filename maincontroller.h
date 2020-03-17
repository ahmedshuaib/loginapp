#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include <QThread>

class NetworkManager;
class MainController : public QObject
{
    Q_OBJECT
    QThread worker_thread;
public:
    explicit MainController(QObject *parent = nullptr);
    ~MainController();

    NetworkManager *manager() { return n_manager; }
    void set_url(const QString &url);
    void submit();

signals:
    void signal_do_work();

public slots:

private:
    NetworkManager *n_manager;
};

#endif // MAINCONTROLLER_H
