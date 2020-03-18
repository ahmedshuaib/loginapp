#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainController;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool validation();

public slots:
    void slots_response_receive(const QByteArray &array);

private slots:
    void on_submit_form_clicked();

private:
    Ui::MainWindow *ui;
    MainController *controller;
};

#endif // MAINWINDOW_H
