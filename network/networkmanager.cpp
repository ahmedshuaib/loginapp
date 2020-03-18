#include "networkmanager.h"
#include <stdio.h>
#include <QDebug>
#include <QString>

NetworkManager *NetworkManager::instance_ = nullptr;

NetworkManager::NetworkManager(QObject *parent) : response(nullptr)
{
    instance_ = this;
    response = new std::string;
    curl = curl_easy_init();
}

NetworkManager::~NetworkManager()
{
    curl_easy_cleanup(curl);
}

void NetworkManager::set_url(const QString &url)
{
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.toLocal8Bit().constData());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    }
}

void NetworkManager::set_post_fields(const char *post_fields)
{
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_fields);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)strlen(post_fields));
}

void NetworkManager::set_method(const QString &method)
{
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, method.toLocal8Bit().constData());
}

void NetworkManager::skip_ssl()
{
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
}

void NetworkManager::execute()
{
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, reponse_writer);
    res = curl_easy_perform(curl);
    if(res != CURLE_OK) {
        fprintf(stderr,  "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));
    }
}

QByteArray NetworkManager::Response()
{
    return response_;
}

void NetworkManager::DoWork()
{
    execute();
}

int NetworkManager::reponse_writer(char *data, size_t size, size_t nmemb, std::string *buffer_in)
{
    int rsize = 0;
    if(buffer_in != nullptr) {
        instance_->signal_response_sender(data);
        rsize = size * nmemb;
        return rsize;
    }
    return rsize;
}
