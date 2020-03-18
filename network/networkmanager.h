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
    void set_post_fields(const char *post_fields);
    void set_method(const QString &method);
    void execute();
    QByteArray Response();

signals:
    void signal_response_sender(const QByteArray &array);


public slots:
    void DoWork();

public:
    static int reponse_writer(char *data, size_t size, size_t nmemb, std::string *buffer_in);

private:
    CURL *curl;
    CURLcode res;
    std::string *response;
    QByteArray response_;
    static NetworkManager *instance_;
};

#endif // NETWORKMANAGER_H
