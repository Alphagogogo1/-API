#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString link="http://restapi.amap.com/v3/weather/weatherInfo?";
    QString city="110101";
    QString key="xxxxx";
    QString stringApi="";
    stringApi=link;
    stringApi+="key="+key;
    stringApi+="&city="+city;

    Manager=new QNetworkAccessManager(this);
    connect(Manager,&QNetworkAccessManager::finished,this,&MainWindow::recWorker);
    QUrl url(stringApi);
    Manager->get(QNetworkRequest(url));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::recWorker(QNetworkReply *reply)
{
    // 判断错误码是否为QNetworkReply::NoError（若判断条件成立，则reply对象数据错误）
    if(reply->error() != QNetworkReply::NoError)
    {
        // 弹出警告
        QMessageBox::warning(nullptr, "警告", "数据返回错误");
    }
    else
    {
        // 创建array容器接收数据
        QByteArray data;
        // 读取所有json串
        data = reply->readAll();
        // 解析json串
        parseJson(data);

    }
}

void MainWindow::parseJson(QByteArray jsonData)
{
    /*将QByteArray类对象转换为QJsonDocument*/
    QJsonDocument jsonDoc=QJsonDocument::fromJson(jsonData);
    QJsonObject jsonObject=jsonDoc.object();
    //qDebug()<<jsonObject.keys()<<endl;
    QJsonObject lives0=jsonObject.value("lives").toArray().at(0).toObject();
    for(auto i:lives0.keys())
    {
        qDebug()<<i<<":"<<lives0.value(i).toString();
    }
}

