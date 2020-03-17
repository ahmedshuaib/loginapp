#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include "curl/curl.h"

class NetworkManager : public QObject
{
    Q_OBJECT
public:
    explicit NetworkManager(QObject *parent = nullptr);
    ~NetworkManager();

    void set_url(const QString &url);
    void skip_ssl();
    void execute();

signals:

public slots:
    void DoWork();


private:
    CURL *curl;
    CURLcode res;
};

#endif // NETWORKMANAGER_H
