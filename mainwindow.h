#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>
#include <QByteArray>
#include <QJsonValue>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:
   void recWorker(QNetworkReply *);
   QNetworkAccessManager *Manager;
   void parseJson(QByteArray jsonData);
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
