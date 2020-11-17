#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    manager = new QNetworkAccessManager(this);

    //connect(manager, SIGNAL(finished(QNetworkReply*)),
    //        this, SLOT(reply_finished(QNetworkReply*)));
    connect(manager, &QNetworkAccessManager::finished,
            this, &Widget::reply_finished);

    qDebug() << "드라이버" << QSqlDatabase::drivers();
    qDebug() << QCoreApplication::libraryPaths();
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("corona");
    db.setUserName("root");
    db.setPassword("1234");

    db.open();

    //model = new QSqlTableModel(this);
    //model->setTable("clinic");
    //ui->tableView->setModel(model);

    query = new QSqlQuery;
    query->exec("select * from clinic");
    //query->exec("select * from dummyclinic");
    query->next();
    QString link;
    QString key;
    QString spot;
    QString combine_link;
    link="https://maps.googleapis.com/maps/api/geocode/json?address=";
    key="&key=AIzaSyD4KYKfd7YvfuGRfAzq24kxNt7B7C_ueGs"; // 인증키....

    spot=query->value(5).toString();
    //spot=query->value(0).toString();
    if(spot.contains(" "))
    {
        spot.replace(" ","+");
        spot.replace("_","+");
    }

    combine_link=link+spot+key;
    qDebug()<<QString::fromLocal8Bit("DB -> address: ")<<spot;
    qDebug()<<QString::fromLocal8Bit("1. API 가동...");
    request.setUrl(QUrl(combine_link));
    manager->get(request);
    //manager->get(QNetworkRequest(QUrl(combine_link)));
}

void Widget::reply_finished(QNetworkReply *reply)
{   // 형섭 방식
    if (reply->error()) {
        qDebug() << reply->errorString();
        return;
    }

    QByteArray array = reply->readAll();
    QJsonDocument document(QJsonDocument::fromJson(array));

    QJsonObject document_object = document.object(); // => 개체화...
    QJsonArray document_array = document_object["results"].toArray();
    QStringList document_key = document_object.keys();

    qDebug() << "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&";
    qDebug() << ">>>>>> 1. document_object : " << document_object;
    qDebug() << ">>>>>> 2. document_key : " << document_key;
    qDebug() << "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&";

    QJsonObject results_object = document_array[0].toObject();
    QJsonObject geometry_object = results_object["geometry"].toObject();
    QJsonObject location_object = geometry_object["location"].toObject();
    QJsonValue lat_value = location_object["lat"];
    QJsonValue lng_value = location_object["lng"];
    qDebug() << "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&";
    qDebug() << ">>>>>> 1. geometry_object : " << geometry_object;
    qDebug() << ">>>>>> 2. location_object : " << location_object;
    qDebug() << ">>>>>> 3. lat_value : " << lat_value;
    qDebug() << ">>>>>> 4. lng_value : " << lng_value;
    qDebug() << "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&";
    //QJsonValue lat_value = location_object.value(QString("lat"));
    //QJsonValue lng_value = location_object.value(QString("lng"));
    double lat=lat_value.toDouble();
    qDebug()<<"[lat] => "<<lat;
    double lng=lng_value.toDouble();
    qDebug()<<"[lng] => "<<lng;

    QSqlQuery extra_queries;
    //extra_queries.exec(QString("update dummyclinic set lat=%2, lng=%3 where address='%1'").arg(query->value(0).toString()).arg(lat).arg(lng));
    extra_queries.exec(QString("update clinic set lat=%2, lng=%3 where address='%1'").arg(query->value(5).toString()).arg(lat).arg(lng));

    if(!query->next())
    {
        return ;
    }

    QString link;
    QString key;
    QString spot;
    QString combine_link;
    link="https://maps.googleapis.com/maps/api/geocode/json?address=";
    key="&key=AIzaSyD4KYKfd7YvfuGRfAzq24kxNt7B7C_ueGs";

    spot=query->value(5).toString();
    //spot=query->value(0).toString();
    if(spot.contains(" "))
    {
        spot.replace(" ","+");
        spot.replace("_","+");
    }

    combine_link=link+spot+key;
    qDebug()<<QString::fromLocal8Bit("DB -> address: ")<<spot;
    qDebug()<<QString::fromLocal8Bit("2. API 재가동...");
    request.setUrl(QUrl(combine_link));
    manager->get(request);

    /* 현우 방식
    QJsonDocument jsonc = QJsonDocument::fromJson(reply->readAll());
    qDebug()<<"[QJsonDocument jsonc] => "<<jsonc;

    QJsonObject result = jsonc.object();
    qDebug() <<"[result] => "<<result;
    QJsonValue value = result.value(QString("results"));
    qDebug() <<"[value] => "<<value;

    QJsonArray subwe = value.toArray();
    QJsonObject subob = subwe[0].toObject();
    QJsonValue subval = subob.value(QString("geometry"));
    qDebug() <<"[subval] => "<<subval;

    QJsonObject location_object = subval.toObject();
    QJsonValue lo= location_object.value(QString("location"));
    qDebug()<<"[lo] => "<<lo;

    QJsonObject saveLat=lo.toObject();
    QJsonValue lat=saveLat.value(QString("lat"));
    double doublelat=lat.toDouble();
    qDebug()<<"[doublelat] => "<<doublelat;

    QJsonObject savelng=lo.toObject();
    QJsonValue lng=savelng.value(QString("lng"));
    double doublelng=lng.toDouble();
    qDebug()<<"[doublelng] => "<<doublelng;
    */
}

Widget::~Widget()
{
    delete ui;
}
