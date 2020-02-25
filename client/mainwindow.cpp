#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <string>
#include "echo.pb.h"
#include <boost/thread/thread.hpp>
#include "RPCServerService.h"
#include <QMessageBox>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::MainWindow)
{
	ui->setupUi(this);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_connectButton_clicked()
{
	ui->logEdit->append("start server");

	QStringList drivers = QSqlDatabase::drivers();
	foreach(QString driver, drivers)
		qDebug() << "\t " << driver;
	qDebug() << "End";

	db = QSqlDatabase::addDatabase("QMYSQL");
	db.setHostName("localhost");
	db.setDatabaseName("qtdemo");
	db.setUserName("root");
	db.setPassword("321");

	bool bisOpenn = db.open();
	qDebug() << "bisOpenn=" << bisOpenn;

	if (db.open())
	{
		QMessageBox::warning(NULL, QStringLiteral("tip"), "open ok", QMessageBox::Yes);
	}
	else
	{
		qDebug() << db.lastError().text();
		QMessageBox::warning(NULL, QStringLiteral("warn"), "open failed", QMessageBox::Yes);
		return;
	}
	QSqlQuery sql_query(db);
	bool buscess = sql_query.exec("create table if not exists  record (id int primary key auto_increment, log varchar(100)");
	client = new TcpClient(ios, this);
	boost::thread t(boost::bind(&boost::asio::io_service::run, &ios));
}

void MainWindow::on_viewDataButton_clicked()
{
	QSqlQuery sql_query(db);
	sql_query.exec("select * from record");
	while (sql_query.next())
	{
		qDebug() << sql_query.value(0).toInt() << sql_query.value(1).toString();
		ui->logEdit->append(sql_query.value(1).toString());
	}
}

void MainWindow::on_exitButton_clicked()
{
	this->close();
}

void MainWindow::on_sendButton_clicked()
{
	QString msg = ui->inputEdit->text();
	echo::EchoRequest request;
	request.set_message(msg.toStdString().c_str());
	echo::EchoService * service = new echo::EchoService::Stub(client->getConnection());
	service->Echo(NULL, &request, NULL, NULL);

}

void MainWindow::updateLog(const std::string msg)
{
	ui->logEdit->append(QString::fromStdString(msg));

	QSqlQuery sql_query(db);
	char sql[100];
	sprintf(sql, "insert into record values( '%s')", msg.c_str());
	bool buscess = sql_query.exec(QString(sql));
	if (!buscess)
	{
		qDebug("table is error");
	}
	else
	{
		qDebug("table is sucess");
	}
}