#include "Location.h"

Location::Location()
{

}

void Location::SetLocation(char* province, char* city, char* medical_institution, char* address, char* weekday_operating_hours, char* saturday_operating_hours, char* sunday_operating_hours, char* representative_phone, char* lat, char* lng)
{
    strcpy(this->province,province);
    strcpy(this->city,city);
    strcpy(this->medical_institution,medical_institution);
    strcpy(this->address,address);
    strcpy(this->weekday_operating_hours,weekday_operating_hours);
    strcpy(this->saturday_operating_hours,saturday_operating_hours);
    strcpy(this->sunday_operating_hours,sunday_operating_hours);
    strcpy(this->representative_phone,representative_phone);
    strcpy(this->lat,lat);
    strcpy(this->lng,lng);
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
    strcpy(this->province,province);
}

void Location::SetCity(char* city)
{
    strcpy(this->city,city);
}

void Location::SetMedical(char* medical_institution)
{
    strcpy(this->medical_institution,medical_institution);
}

void Location::SetAddress(char* address)
{
    strcpy(this->address,address);
}

void Location::SetWeekday(char* weekday_operating_hours)
{
    strcpy(this->weekday_operating_hours,weekday_operating_hours);
}

void Location::SetSaturday(char* saturday_operating_hours)
{
    strcpy(this->saturday_operating_hours,saturday_operating_hours);
}

void Location::SetSunday(char* sunday_operating_hours)
{
    strcpy(this->sunday_operating_hours,sunday_operating_hours);
}

void Location::SetPhone(char* representative_phone)
{
    strcpy(this->representative_phone,representative_phone);
}

void Location::SetLat(char* lat)
{
    strcpy(this->lat,lat);
}
void Location::SetLng(char* lng)
{
    strcpy(this->lng,lng);
}

void Location::ShowLocation()
{
    cout<<"도: "<<province<<" 시: "<<city<<" 건물: "<<medical_institution<<" 주소: "<<address<<" 평일: "<<weekday_operating_hours
            <<" 토요일: "<<saturday_operating_hours<<" 일요일: "<<sunday_operating_hours<<" 전화: "<<representative_phone<<" 위도: "<<lat<<" 경도: "<<lng<<endl;
}