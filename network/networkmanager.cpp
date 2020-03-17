#include "networkmanager.h"
#include <stdio.h>
#include <QDebug>

NetworkManager::NetworkManager(QObject *parent)
{
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

void NetworkManager::skip_ssl()
{
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
}

void NetworkManager::execute()
{
    res = curl_easy_perform(curl);
    if(res != CURLE_OK) {
        fprintf(stderr,  "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));
    }
}

void NetworkManager::DoWork()
{
    execute();
}
