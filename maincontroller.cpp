#include "maincontroller.h"
#include "network/networkmanager.h"

MainController::MainController(QObject *parent) : QObject(parent)
{
    n_manager = new NetworkManager;
    n_manager->moveToThread(&worker_thread);
    connect(&worker_thread, &QThread::finished, n_manager, &QObject::deleteLater);
    connect(this, &MainController::signal_do_work, n_manager, &NetworkManager::DoWork);
    worker_thread.start();
}

MainController::~MainController()
{
    worker_thread.quit();
    worker_thread.wait();
}

void MainController::set_url(const QString &url)
{
    n_manager->set_url(url);
}

void MainController::submit()
{
    emit signal_do_work();
}
