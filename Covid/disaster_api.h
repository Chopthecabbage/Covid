#ifndef DISASTER_API_H
#define DISASTER_API_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QDebug>
#include <QByteArray>
#include <QUrl>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>
#include <QtWebEngineWidgets/QtWebEngineWidgets>
#include <QWebEngineView>
#include <QWebEnginePage>
#include <QEventLoop>
#include "disaster_msg.h"

class Disaster_API : public QObject
{
     Q_OBJECT
private:
    QNetworkAccessManager *manager;
    QEventLoop loop;
    QDate selected_date;
    QString selected_loc;
    int api_page;

public:
    Disaster_API();
    Disaster_API(QDate selected_date, QString selected_loc, int api_page);
    ~Disaster_API();
    void Request_API(QVector<Disaster_Msg> &loc_msg);
};

#endif // DISASTER_API_H

