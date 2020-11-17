#include "location.h"

Location::Location()
{

}

void Location::SetLocation(char* province, char* city, char* medical_institution, char* address, char* weekday_operating_hours, char* saturday_operating_hours, char* sunday_operating_hours, char* representative_phone, char* lat, char* lng)
{
    strcpy_s(this->province,province);
    strcpy_s(this->city,city);
    strcpy_s(this->medical_institution,medical_institution);
    strcpy_s(this->address,address);
    strcpy_s(this->weekday_operating_hours,weekday_operating_hours);
    strcpy_s(this->saturday_operating_hours,saturday_operating_hours);
    strcpy_s(this->sunday_operating_hours,sunday_operating_hours);
    strcpy_s(this->representative_phone,representative_phone);
    strcpy_s(this->lat,lat);
    strcpy_s(this->lng,lng);
}

char* Location::GetProvince()
{
    return province;
}

char* Location::GetCity()
{
    return city;
}

char* Location::GetMedical()
{
    return medical_institution;
}

char* Location::GetAddress()
{
    return address;
}

char* Location::GetWeekday()
{
    return weekday_operating_hours;
}

char* Location::GetSaturday()
{
    return saturday_operating_hours;
}

char* Location::GetSunday()
{
    return sunday_operating_hours;
}

char* Location::GetPhone()
{
    return representative_phone;
}

char* Location::GetLat()
{
    return lat;
}

char* Location::GetLng()
{
    return lng;
}

void Location::SetProvince(char* province)
{
    strcpy_s(this->province,province);
}

void Location::SetCity(char* city)
{
    strcpy_s(this->city,city);
}

void Location::SetMedical(char* medical_institution)
{
    strcpy_s(this->medical_institution,medical_institution);
}

void Location::SetAddress(char* address)
{
    strcpy_s(this->address,address);
}

void Location::SetWeekday(char* weekday_operating_hours)
{
    strcpy_s(this->weekday_operating_hours,weekday_operating_hours);
}

void Location::SetSaturday(char* saturday_operating_hours)
{
    strcpy_s(this->saturday_operating_hours,saturday_operating_hours);
}

void Location::SetSunday(char* sunday_operating_hours)
{
    strcpy_s(this->sunday_operating_hours,sunday_operating_hours);
}

void Location::SetPhone(char* representative_phone)
{
    strcpy_s(this->representative_phone,representative_phone);
}

void Location::SetLat(char* lat)
{
    strcpy_s(this->lat,lat);
}
void Location::SetLng(char* lng)
{
    strcpy_s(this->lng,lng);
}

void Location::ShowLocation()
{
    //qDebug()<<QString::fromLocal8Bit("도: ")<<QString::fromLocal8Bit(province)<<QString::fromLocal8Bit(" 시: ")<<QString::fromLocal8Bit(city)<<QString::fromLocal8Bit(" 건물: ")<<QString::fromLocal8Bit(medical_institution)<<QString::fromLocal8Bit(" 주소: ")<<QString::fromLocal8Bit(address)<<QString::fromLocal8Bit(" 평일: ")<<QString::fromLocal8Bit(weekday_operating_hours)
    //        <<QString::fromLocal8Bit(" 토요일: ")<<QString::fromLocal8Bit(saturday_operating_hours)<<QString::fromLocal8Bit(" 일요일: ")<<QString::fromLocal8Bit(sunday_operating_hours)<<QString::fromLocal8Bit(" 전화: ")<<QString::fromLocal8Bit(representative_phone)<<QString::fromLocal8Bit(" 위도: ")<<QString::fromLocal8Bit(lat)<<QString::fromLocal8Bit(" 경도: ")<<QString::fromLocal8Bit(lng);
    qDebug()<<QString::fromLocal8Bit("도: ")<<province<<QString::fromLocal8Bit(" 시: ")<<city<<QString::fromLocal8Bit(" 건물: ")<<medical_institution<<QString::fromLocal8Bit(" 주소: ")<<address<<QString::fromLocal8Bit(" 평일: ")<<weekday_operating_hours
            <<QString::fromLocal8Bit(" 토요일: ")<<saturday_operating_hours<<QString::fromLocal8Bit(" 일요일: ")<<sunday_operating_hours<<QString::fromLocal8Bit(" 전화: ")<<representative_phone<<QString::fromLocal8Bit(" 위도: ")<<lat<<QString::fromLocal8Bit(" 경도: ")<<lng;
}
