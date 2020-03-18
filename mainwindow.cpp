#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "maincontroller.h"
#include "network/networkmanager.h"
#include <QMessageBox>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

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
    QStringList propertyNames;
    QStringList propertyKeys;
    QString strReplay = (QString)array;
    qInfo() << strReplay;
    QJsonDocument json_response = QJsonDocument::fromJson(strReplay.toUtf8());
    QJsonObject json_object = json_response.object(); //make object


    auto obj = json_object["form"].toObject();

    qInfo() << "Foo : " <<  obj["foo1"].toString();
    qInfo() << "Foo2: " <<  obj["foo2"].toString();

//    QJsonArray json_array = json_object["properties"].toArray(); //make an array for []


    //for json array
//    foreach (const QJsonValue & value, json_array) {
//        QJsonObject obj = value.toObject();
//    }
}

void MainWindow::on_submit_form_clicked()
{
    if(!validation()) {
        QMessageBox::information(this, "Incorrect information", "Username or password field are empty?");
    }

    controller->set_url("https://postman-echo.com/post");
    controller->manager()->set_post_fields("foo1=bar1&foo2=bar2");
    controller->manager()->skip_ssl();
    controller->submit();

}
