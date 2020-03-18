#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "maincontroller.h"
#include "network/networkmanager.h"
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    controller = new MainController(this);
    connect(controller, &MainController::signal_response_receive, this, &MainWindow::slots_response_receive);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::validation()
{
    if(ui->user_name->text().isEmpty())
        return (false);
    if(ui->user_password->text().isEmpty())
        return (false);
    return (true);
}

void MainWindow::slots_response_receive(const QByteArray &array)
{
    qInfo() << array;
}

void MainWindow::on_submit_form_clicked()
{
    if(!validation()) {
        QMessageBox::information(this, "Incorrect information", "Username or password field are empty?");
    }

    controller->set_url("https://google.com");
//    controller->manager()->set_post_fields("foo1=bar1&foo2=bar2");
    controller->manager()->skip_ssl();
    controller->submit();
    qInfo() << "Resonse: " << controller->manager()->Response();

}
