#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <string>

#include "TcpConnect.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

	void updateLog(const std::string msg);

private slots:
    void on_connectButton_clicked();

    void on_viewDataButton_clicked();

    void on_exitButton_clicked();

    void on_sendButton_clicked();

private:
    Ui::MainWindow *ui;

	io_service ios;
	TcpClient *client;
	QSqlDatabase db;

};

#endif // MAINWINDOW_H
