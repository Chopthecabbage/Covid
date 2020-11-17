#include "disaster_msg.h"

Disaster_Msg::Disaster_Msg()
{
    date_time = "";
    loc_name = "";
    msg = "";
}
Disaster_Msg::Disaster_Msg(QString date_time, QString loc_name, QString msg)
{
    this->date_time = date_time;
    this->loc_name = loc_name;
    this->msg = msg;
}
void Disaster_Msg::Set_Disaster_Msg(QString date_time, QString loc_name, QString msg)
{
    this->date_time = date_time;
    this->loc_name = loc_name;
    this->msg = msg;
}
void Disaster_Msg::Set_Date_Time(QString date_time)
{
    this->date_time = date_time;
}
void Disaster_Msg::Set_Loc_Name(QString loc_name)
{
    this->loc_name = loc_name;
}
void Disaster_Msg::Set_Msg(QString msg)
{
    this->msg = msg;
}
QString Disaster_Msg::Get_Msg() const
{
    return msg;
}
QString Disaster_Msg::Get_Loc_Name() const
{
    return loc_name;
}
QString Disaster_Msg::Get_Date() const
{
    QStringList temp = date_time.split(' ');
    QString date(temp[0]);
    return date;
}
QString Disaster_Msg::Get_Time() const
{
    QStringList list = date_time.split(' ');
    QString time = list[1].split(':')[0] + ':' + list[1].split(':')[1];
    return time;
}
