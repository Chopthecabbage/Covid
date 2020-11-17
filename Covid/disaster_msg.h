#ifndef DISASTER_MSG_H
#define DISASTER_MSG_H

#include <QString>
#include <QStringList>

class Disaster_Msg
{
private:
    QString date_time; // 생성일시
    QString loc_name; // 수신지역 이름
    QString msg; // 메시지
public:
    Disaster_Msg();
    Disaster_Msg(QString date_time, QString loc_name, QString msg);
    void Set_Disaster_Msg(QString date, QString loc_name, QString msg);
    void Set_Date_Time(QString date_time);
    void Set_Loc_Name(QString loc_name);
    void Set_Msg(QString msg);
    QString Get_Msg() const;
    QString Get_Loc_Name() const;
    QString Get_Date() const;
    QString Get_Time() const;
};

#endif // DISASTER_MSG_H
