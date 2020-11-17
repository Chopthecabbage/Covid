#include "disaster_api.h"

Disaster_API::Disaster_API()
{ }

Disaster_API::Disaster_API(QDate selected_date, QString selected_loc, int api_page)
{
    this->selected_date = selected_date;
    this->selected_loc = selected_loc;
    this->api_page = api_page;
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));
}
Disaster_API::~Disaster_API()
{
    delete manager;
}

void Disaster_API::Request_API(QVector<Disaster_Msg> &loc_msg)
{
    QString url;
    url = "http://apis.data.go.kr/1741000/DisasterMsg2/getDisasterMsgList?";
    url += "ServiceKey=ZxLg9pD21T120Y8r8s%2FrIQiQ%2Fk3bNqB9OvHiPsxjCAmTjzLhperD1b6q1WjyXaqPVsY7RE4N0WjydC3HxkMdeA%3D%3D";
    url += "&type=json";
    url += "&pageNo=";
    url += QString::number(api_page);
    url += "&numOfRows=1000";
    url += "&flag=Y";

    QNetworkReply *reply = manager->get(QNetworkRequest(QUrl(url)));
    loop.exec();

    QByteArray jsonText=reply->readAll();
    QJsonDocument json_doc(QJsonDocument::fromJson(jsonText));

    QJsonObject json_obj = json_doc.object();
    QJsonArray json_arr = json_obj["DisasterMsg"].toArray();

    QJsonObject row_obj = json_arr[1].toObject();
    QJsonArray row_arr = row_obj["row"].toArray();

    int i = 0;
    while(i < 1000)
    {
        QJsonObject val_obj = row_arr[i].toObject();
        QJsonValue val_loc_name = val_obj.value(QString("location_name"));
        QJsonValue val_date_time = val_obj.value(QString("create_date"));
        QJsonValue val_msg = val_obj.value(QString("msg"));

        QStringList str_list = val_date_time.toString().split(' ');
        QDate temp_date = QDate::fromString(str_list[0], "yyyy/MM/dd");

        // 데이터가 없어서 지나간경우 남은 연산 안하게 멈춤
        if(temp_date < selected_date) break;
        // 선택한 날짜 맞나 체크
        bool check_date = selected_date == temp_date;
        // 선택한 지역명 포함하나 체크
        bool check_loc = val_loc_name.toString().contains(selected_loc, Qt::CaseInsensitive);

        if(check_date && check_loc)
        {
            Disaster_Msg temp(val_date_time.toString(), val_loc_name.toString(), val_msg.toString());
            loc_msg.push_back(temp);
        }
        i++;
     }
}

